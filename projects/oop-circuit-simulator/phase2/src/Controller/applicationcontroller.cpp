// =======================================================================
// FILE: applicationcontroller.cpp
// =======================================================================
#include "applicationcontroller.h"
#include <fstream>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

ApplicationController::ApplicationController(QObject *parent) : QObject(parent) {}

CircuitModel* ApplicationController::getModel() { return &model; }

// --- متدهای جدید برای مدیریت تک‌قطبی‌ها ---

void ApplicationController::scanForSubcircuits() {
    availableSubcircuits.clear();
    
    // Check if QCoreApplication is available
    if (!QCoreApplication::instance()) {
        qDebug() << "QCoreApplication not available, skipping subcircuit scan";
        return;
    }
    
    QString appDir = QCoreApplication::applicationDirPath();
    if (appDir.isEmpty()) {
        qDebug() << "Application directory path is empty, skipping subcircuit scan";
        return;
    }
    
    QDir libraryDir(appDir + "/library");
    if (!libraryDir.exists()) {
        if (!libraryDir.mkpath(".")) {
            qDebug() << "Failed to create library directory:" << libraryDir.absolutePath();
            return;
        }
    }

    QStringList filters;
    filters << "*.sub"; // پسوند فایل‌های تک‌قطبی
    libraryDir.setNameFilters(filters);

    QFileInfoList fileList = libraryDir.entryInfoList();
    for (const QFileInfo &fileInfo : fileList) {
        availableSubcircuits.append(fileInfo.baseName());
    }
    emit libraryChanged(); // به View اطلاع بده که لیست کتابخانه تغییر کرده
}

QStringList ApplicationController::getAvailableSubcircuits() const {
    return availableSubcircuits;
}

void ApplicationController::addSubcircuitToProject(const QString& name) {
    QString filePath = QCoreApplication::applicationDirPath() + "/library/" + name + ".sub";
    std::ifstream is(filePath.toStdString(), std::ios::binary);
    if(is.is_open()){
        try {
            cereal::BinaryInputArchive archive(is);
            auto subcircuit = std::make_shared<SubCircuit>();
            archive(*subcircuit);
            
            // Create new nodes for the subcircuit pins
            auto pin1Node = std::make_shared<Node>(name.toStdString() + "_pin1", 0, 0);
            auto pin2Node = std::make_shared<Node>(name.toStdString() + "_pin2", 120, 0);
            
            // Set the pin nodes for the subcircuit
            subcircuit->node1 = pin1Node;
            subcircuit->node2 = pin2Node;
            
            // Add nodes and subcircuit to project
            model.getProjectData().nodes.push_back(pin1Node);
            model.getProjectData().nodes.push_back(pin2Node);
            model.getProjectData().elements.push_back(subcircuit);
            
            emit statusMessageChanged("تک‌قطبی " + name + " به مدار اضافه شد. روی شماتیک کلیک کنید تا قرار گیرد.");
            emit projectLoaded(); // Refresh the view
        } catch (const std::exception& e) {
            emit statusMessageChanged("خطا در پردازش فایل تک‌قطبی: " + QString(e.what()));
        }
    } else {
        emit statusMessageChanged("خطا در بارگذاری تک‌قطبی: " + name);
    }
}

bool ApplicationController::saveAsSubcircuit(const QString& name) {
    if (name.isEmpty()) return false;

    SubCircuit subcircuit;
    // Copy current project's logical data as subcircuit definition
    subcircuit.internalElements = model.getProjectData().elements;
    subcircuit.internalNodes = model.getProjectData().nodes;
    
    // Get selected pins from GraphicsView (if available)
    // For now, use default pins: first two nodes
    subcircuit.pinNodeIndices.clear();
    if (!subcircuit.internalNodes.empty()) {
        subcircuit.pinNodeIndices.push_back(0);
        if (subcircuit.internalNodes.size() > 1)
            subcircuit.pinNodeIndices.push_back(1);
    }

    QString filePath = QCoreApplication::applicationDirPath() + "/library/" + name + ".sub";
    std::ofstream os(filePath.toStdString(), std::ios::binary);
    if(os.is_open()){
        cereal::BinaryOutputArchive archive(os);
        archive(subcircuit);
        emit statusMessageChanged("مدار فعلی با نام " + name + " در کتابخانه ذخیره شد.");
        scanForSubcircuits(); // کتابخانه را دوباره اسکن کن
        return true;
    } else {
        emit statusMessageChanged("خطا در ذخیره تک‌قطبی.");
        return false;
    }
}

bool ApplicationController::saveAsSubcircuitWithPins(const QString& name, const std::vector<std::shared_ptr<Node>>& pins) {
    if (name.isEmpty() || pins.size() != 2) return false;

    SubCircuit subcircuit;
    // Copy current project's logical data as subcircuit definition
    subcircuit.internalElements = model.getProjectData().elements;
    subcircuit.internalNodes = model.getProjectData().nodes;
    
    // Use the selected pins
    subcircuit.pinNodeIndices.clear();
    for (const auto& pin : pins) {
        // Find the index of the pin in internalNodes
        for (size_t i = 0; i < subcircuit.internalNodes.size(); ++i) {
            if (subcircuit.internalNodes[i] && subcircuit.internalNodes[i]->getName() == pin->getName()) {
                subcircuit.pinNodeIndices.push_back(i);
                break;
            }
        }
    }
    
    // Ensure we have exactly 2 pins
    if (subcircuit.pinNodeIndices.size() != 2) {
        emit statusMessageChanged("خطا: نتوانستیم پین‌های انتخاب شده را پیدا کنیم.");
        return false;
    }

    QString filePath = QCoreApplication::applicationDirPath() + "/library/" + name + ".sub";
    std::ofstream os(filePath.toStdString(), std::ios::binary);
    if(os.is_open()){
        cereal::BinaryOutputArchive archive(os);
        archive(subcircuit);
        emit statusMessageChanged("تک‌قطبی " + name + " با پین‌های انتخاب شده ذخیره شد.");
        scanForSubcircuits(); // کتابخانه را دوباره اسکن کن
        return true;
    } else {
        emit statusMessageChanged("خطا در ذخیره تک‌قطبی.");
        return false;
    }
}

// --- پایان متدهای جدید ---


void ApplicationController::createNewProject() {
    try {
        model.getProjectData().clear();
        emit projectLoaded();
        emit statusMessageChanged("پروژه جدید ایجاد شد.");
    } catch (const std::exception& e) {
        qDebug() << "Error creating new project:" << e.what();
        emit statusMessageChanged("خطا در ایجاد پروژه جدید.");
    } catch (...) {
        qDebug() << "Unknown error creating new project";
        emit statusMessageChanged("خطای نامشخص در ایجاد پروژه جدید.");
    }
}
void ApplicationController::runAnalysis(const SimulationSettings& settings) {
    emit statusMessageChanged("تحلیل در حال اجرا است...");
    std::string outputFilePath = "analysis_result.txt";
    bool success = model.runAnalysis(settings, outputFilePath);
    if (success) {
        emit statusMessageChanged("تحلیل با موفقیت انجام شد.");
        emit analysisCompleted(QString::fromStdString(outputFilePath));
    } else {
        emit statusMessageChanged("خطا در اجرای تحلیل.");
    }
}
void ApplicationController::saveProject(const QString& filePath) {
    if (filePath.isEmpty()) return;
    emit statusMessageChanged("در حال ذخیره پروژه...");
    std::ofstream os(filePath.toStdString(), std::ios::binary);
    if(os.is_open()){
        cereal::BinaryOutputArchive archive(os);
        archive(model.getProjectData());
        emit statusMessageChanged("پروژه با موفقیت در " + filePath + " ذخیره شد.");
    } else {
        emit statusMessageChanged("خطا: امکان باز کردن فایل برای ذخیره وجود ندارد.");
    }
}
void ApplicationController::loadProject(const QString& filePath) {
    if (filePath.isEmpty()) return;
    emit statusMessageChanged("در حال بارگذاری پروژه...");
    std::ifstream is(filePath.toStdString(), std::ios::binary);
    if(is.is_open()){
        cereal::BinaryInputArchive archive(is);
        archive(model.getProjectData());
        emit projectLoaded();
        emit statusMessageChanged("پروژه با موفقیت از " + filePath + " بارگذاری شد.");
    } else {
        emit statusMessageChanged("خطا: فایل پروژه یافت نشد.");
    }
}
