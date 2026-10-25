/*
 * ============================================================
 *  همهٔ محتوای سایت در همین فایل است.
 *  All site content lives in this file.
 * ============================================================
 *  - هر متن دوزبانه به شکل { fa: "...", en: "..." } نوشته می‌شود.
 *  - متن‌های بلند (bio, description) از قالب ساده پشتیبانی می‌کنند:
 *      **پررنگ**   [متن لینک](https://...)   خط خالی = پاراگراف جدید   "- " = فهرست
 *  - تصاویر را در assets/img و فایل‌ها (PDF، کد) را در assets/files بگذارید.
 *  - بخش‌هایی که خالی باشند ([]) در سایت نمایش داده نمی‌شوند.
 */

window.SITE = {
  defaultLang: "fa",
  repo: "https://github.com/seyedkiarash/seyedkiarash.github.io", // برای نمایش نوت‌بوک‌ها روی GitHub

  profile: {
    name: { fa: "سید کیارش اشراقی نائینی", en: "Seyed Kiarash Eshraghi Naeini" },
    title: {
      fa: "دانشجوی کارشناسی مهندسی برق، دانشگاه صنعتی شریف",
      en: "B.Sc. Student in Electrical Engineering, Sharif University of Technology"
    },
    location: { fa: "تهران، ایران", en: "Tehran, Iran" },
    photo: "", // مثال: "assets/img/profile.jpg"
    bio: {
      fa: "دانشجوی کارشناسی مهندسی برق در دانشگاه صنعتی شریف هستم و در آزمایشگاه چندرسانه‌ای دکتر آرش امینی همکاری پژوهشی دارم. علاقهٔ اصلی‌ام **پردازش سیگنال** است؛ به‌ویژه تبدیل صدا، پردازش سیگنال روی گراف برای تصویر و صوت، شبکه‌های عصبی کانولوشنی و حسگری فشرده.\n\nدر کنار پژوهش، دستیار آموزشی چند درس برنامه‌نویسی، مدار، الکترومغناطیس و آمار و احتمال بوده‌ام. در این صفحه پروژه‌ها و فعالیت‌های دوران دانشگاهم را، همراه با گزارش‌ها و کدها، گردآوری کرده‌ام.",
      en: "I am an undergraduate Electrical Engineering student at Sharif University of Technology and a research collaborator at Dr. Arash Amini's Multimedia Lab. My main interest is **signal processing** — in particular voice conversion, graph signal processing for images and audio, convolutional neural networks, and compressed sensing.\n\nAlongside research, I have served as a teaching assistant for courses in programming, circuit theory, electromagnetics, and probability & statistics. This site collects my university projects and activities, together with their reports and code."
    },
    interests: {
      fa: ["تبدیل صدا", "پردازش سیگنال روی گراف (تصویر و صوت)", "شبکه‌های عصبی کانولوشنی", "حسگری فشرده"],
      en: ["Voice Conversion", "Graph Signal Processing (Image & Audio)", "Convolutional Neural Networks", "Compressed Sensing"]
    },
    email: ["8kia.eshraghi4@gmail.com", "kiarash.eshraghi84@sharif.edu"],
    links: [
      { type: "github", label: "GitHub", url: "https://github.com/seyedkiarash" }
      // { type: "linkedin", label: "LinkedIn", url: "https://www.linkedin.com/in/..." },
    ],
    cvPdf: { fa: "", en: "" }
  },

  education: [
    {
      degree: { fa: "کارشناسی مهندسی برق", en: "B.Sc. in Electrical Engineering" },
      school: { fa: "دانشگاه صنعتی شریف", en: "Sharif University of Technology" },
      period: { fa: "۱۴۰۳ – اکنون", en: "2024 – Present" },
      gpa: { fa: "معدل کل: ۱۸٫۵۹ از ۲۰", en: "GPA: 18.59 / 20" },
      details: { fa: "", en: "" }
    }
  ],

  achievements: [
    {
      year: { fa: "۱۴۰۳", en: "2024" },
      title: {
        fa: "رتبهٔ ۱۹۸ کنکور سراسری، گروه ریاضی و فنی",
        en: "Ranked 198th, Iranian National University Entrance Exam (Mathematics & Physics)"
      },
      description: { fa: "", en: "" }
    },
    {
      year: { fa: "۱۴۰۲", en: "2023" },
      title: {
        fa: "مدال برنز المپیاد فیزیک کشوری",
        en: "Bronze Medal, Iranian National Physics Olympiad"
      },
      description: { fa: "", en: "" }
    }
  ],

  /*
   * مهارت‌ها — هر مورد می‌تواند یک متن ساده باشد ("LaTeX")
   * یا یک شیء با سطح: { name: "C++", level: {fa,en}, note: {fa,en} }
   */
  skills: [
    {
      group: { fa: "برنامه‌نویسی", en: "Programming" },
      items: [
        { name: "C++", level: { fa: "خوب", en: "Proficient" } },
        { name: "Python", note: { fa: "پردازش سیگنال و جبر خطی", en: "signal processing & linear algebra" }, level: { fa: "خوب", en: "Proficient" } },
        { name: "Python", note: { fa: "آمار و یادگیری ماشین", en: "statistics & machine learning" }, level: { fa: "متوسط", en: "Intermediate" } },
        { name: "MATLAB", level: { fa: "متوسط", en: "Intermediate" } },
        { name: "Verilog", level: { fa: "متوسط", en: "Intermediate" } }
      ]
    },
    { group: { fa: "کتابخانه‌ها و ابزارها", en: "Libraries & Tools" }, items: ["Vivado", "Git", "NumPy", "SciPy", "Matplotlib", "Jupyter", "LaTeX"] },
    {
      group: { fa: "زبان", en: "Languages" },
      items: [
        { name: { fa: "فارسی", en: "Persian" }, level: { fa: "زبان مادری", en: "Native" } },
        { name: { fa: "انگلیسی", en: "English" }, level: { fa: "خوب", en: "Upper-Intermediate" } },
        { name: { fa: "کره‌ای", en: "Korean" }, level: { fa: "مبتدی", en: "Beginner" } }
      ]
    }
  ],

  projects: [
    {
      id: "fpga-logic-lab",
      featured: true,
      title: {
        fa: "آزمایشگاه مدار منطقی روی FPGA",
        en: "Logic Circuits Lab on FPGA"
      },
      year: { fa: "پاییز ۱۴۰۴", en: "Fall 2025" },
      context: {
        fa: "آزمایشگاه مدار منطقی، دکتر محمدرضا موحدین — ۳۲ طراحی Verilog روی برد Zynq-7010",
        en: "Logic Circuits Laboratory, Dr. Mohammad Reza Movahhedin — 32 Verilog designs on a Zynq-7010 board"
      },
      tags: ["Verilog", "FPGA", "Vivado", { fa: "طراحی دیجیتال", en: "Digital Design" }],
      cover: "assets/img/logic-lab/cover.webp",
      summary: {
        fa: "از انکودر اولویت و کد همینگ تا مالتی‌پلکس نمایشگر ۷-سگمنت، کرنومتر، بازی‌های FPGA و کلاک‌دهی از پردازندهٔ Zynq؛ با تست‌بنچ خودارزیاب برای هر طراحی و گزارش LaTeX برای هر آزمایش.",
        en: "From priority encoders and Hamming codes to seven-segment multiplexing, a stopwatch, FPGA games and clocking from the Zynq processor — with a self-checking testbench for every design and a LaTeX report per experiment."
      },
      description: {
        fa: "طراحی‌های Verilog پنج آزمایش این درس، پیاده‌سازی‌شده با Vivado روی برد Zynq-7010 (کلاک ۵۰ مگاهرتز) و برد توسعه‌ای با کلید DIP، نمایشگر چهاررقمی ۷-سگمنت، LED و کلید فشاری.\n\n- **آزمایش ۳:** انکودر اولویت و اثر قطبیت کلیدهای فشاری\n- **آزمایش ۴:** جمع‌کنندهٔ ریپل‌کری، جمع/تفریق مکمل دو با تشخیص سرریز، کد همینگ (۷،۴) و کد SECDED (۸،۴)\n- **آزمایش میان‌ترم:** دیکودر، جمع‌کنندهٔ BCD، مقایسه‌گرها (رفتاری و با پرچم‌های تفریق‌گر)، مالتی‌پلکسر، ضرب‌کنندهٔ ۴×۴ و مقایسه‌گری که فقط با مالتی‌پلکسر ساخته شده\n- **آزمایش ۶:** تقسیم کلاک، الگوهای LED با کنترل سرعت، بازی واکنش و پینگ‌پنگ با بلاک‌دیزاین، و کلاک‌دهی منطق FPGA از پردازندهٔ Zynq\n- **آزمایش ۷:** مالتی‌پلکس نمایشگر ۷-سگمنت، متن متحرک، کرنومتر با شمارنده‌های آبشاری، کنترل شروع/توقف/ریست و انیمیشن مار\n\n**صحت‌سنجی:** برای هر طراحی یک تست‌بنچ خودارزیاب در Icarus Verilog نوشته شد. طراحی‌های ترکیبی برای همهٔ ورودی‌ها (و کدهای همینگ برای همهٔ الگوهای خطای تک و دوبیتی) آزموده شدند و طراحی‌های ترتیبی با سناریو؛ مثلاً یک دور کامل ده‌دقیقه‌ای کرنومتر. هر ۳۲ تست موفق است و همهٔ طراحی‌ها بدون خطا و بدون latch با Yosys سنتز می‌شوند. خطاهای پیداشده در این بررسی اصلاح و در گزارش‌ها مستند شده‌اند، و دو طراحی امتیازی که در آزمایشگاه نیمه‌کاره مانده بودند (انیمیشن مار و نسخهٔ دوم بازی پینگ‌پنگ با دکمه‌های debounce‌شده) کامل شدند.",
        en: "Verilog designs from five experiments of the course, implemented with Vivado on a Zynq-7010 board (50 MHz clock) with an extension board of DIP switches, a 4-digit seven-segment display, LEDs and push buttons.\n\n- **Experiment 3:** priority encoder and push-button polarity\n- **Experiment 4:** ripple-carry adder, two's-complement add/subtract with overflow, Hamming(7,4) and SECDED (8,4) codes\n- **Midterm experiment:** decoder, BCD adder, comparators (behavioural and from subtractor flags), multiplexer, 4×4 multiplier and a comparator built only from multiplexers\n- **Experiment 6:** clock division, LED patterns with speed control, reaction and ping-pong games in block designs, PL logic clocked from the Zynq processor\n- **Experiment 7:** seven-segment multiplexing, scrolling text, a stopwatch from cascaded counters, start/stop/reset control and a snake animation\n\n**Verification:** every design has a self-checking Icarus Verilog testbench — exhaustive for the combinational designs (all inputs; all single and double error patterns for the Hamming codes) and scenario-based for the sequential ones, e.g. a complete 10-minute stopwatch cycle. All 32 pass, and every design synthesises with Yosys without errors or latches. Errors found during the review are corrected and documented in the reports, and two bonus designs left unfinished in the lab — the snake animation and a second ping-pong game with debounced buttons — were completed."
      },
      images: [
        { src: "assets/img/logic-lab/lab07_part3_frames.webp", caption: { fa: "مالتی‌پلکس زمانی: در هر لحظه فقط یک رقم روشن است", en: "Time-multiplexing: one digit is enabled at a time" } },
        { src: "assets/img/logic-lab/lab07_part6_wave.webp", caption: { fa: "شبیه‌سازی کرنومتر: شمارنده‌های آبشاری", en: "Stopwatch simulation: cascaded counters" } },
        { src: "assets/img/logic-lab/lab07_snake.webp", caption: { fa: "انیمیشن مار، بازسازی‌شده از شبیه‌سازی", en: "Snake animation reconstructed from the simulation" } },
        { src: "assets/img/logic-lab/lab06_minigame_wave.webp", caption: { fa: "شبیه‌سازی بازی واکنش", en: "Reaction game simulation" } }
      ],
      files: [
        { label: { fa: "گزارش آزمایش ۷ — نمایشگر ۷-سگمنت و کرنومتر", en: "Report — Experiment 7: seven-segment display and stopwatch" }, url: "labs/logic-circuits-lab/reports/lab07.pdf" },
        { label: { fa: "گزارش آزمایش ۶ — منطق ترتیبی، بازی‌ها و کلاک Zynq", en: "Report — Experiment 6: sequential logic, games, Zynq clocking" }, url: "labs/logic-circuits-lab/reports/lab06.pdf" },
        { label: { fa: "گزارش آزمایش میان‌ترم — دیکودر، BCD، مقایسه‌گر، مالتی‌پلکسر", en: "Report — Midterm experiment: decoders, BCD, comparators, multiplexers" }, url: "labs/logic-circuits-lab/reports/midterm.pdf" },
        { label: { fa: "گزارش آزمایش ۴ — جمع‌کننده‌ها و کدهای همینگ", en: "Report — Experiment 4: adders and Hamming codes" }, url: "labs/logic-circuits-lab/reports/lab04.pdf" },
        { label: { fa: "گزارش آزمایش ۳ — انکودر اولویت", en: "Report — Experiment 3: priority encoder" }, url: "labs/logic-circuits-lab/reports/lab03.pdf" }
      ],
      links: [
        { label: { fa: "کد، تست‌بنچ‌ها و فایل‌های constraint در GitHub", en: "Code, testbenches and constraints on GitHub" }, url: "https://github.com/seyedkiarash/seyedkiarash.github.io/tree/main/labs/logic-circuits-lab" }
      ]
    },
    {
      id: "oop-circuit-simulator",
      featured: true,
      title: {
        fa: "شبیه‌ساز مدار الکتریکی به زبان C++",
        en: "Circuit Simulator in C++"
      },
      year: { fa: "بهار ۱۴۰۴", en: "Spring 2025" },
      context: {
        fa: "پروژهٔ گروهی درس برنامه‌سازی شیءگرا — دکتر عبدالله آراسته",
        en: "Object-Oriented Programming team project — Dr. Abdollah Arasteh"
      },
      tags: ["C++", "Qt", "Eigen", { fa: "تحلیل گره‌ای اصلاح‌شده", en: "MNA" }, { fa: "طراحی شیءگرا", en: "OOP Design" }],
      cover: "assets/img/oop/cover.webp",
      summary: {
        fa: "شبیه‌سازی شبیه SPICE در سه فاز: طراحی شیءگرا، شبیه‌ساز خط فرمان با تحلیل گره‌ای اصلاح‌شده (MNA) و تحلیل گذرا، و نسخهٔ گرافیکی با Qt شامل ویرایشگر شماتیک، نمایشگر شکل موج، ذخیرهٔ پروژه و ارتباط شبکه‌ای؛ همراه با گزارش بازبینی کد.",
        en: "A SPICE-like simulator built in three phases — an object-oriented design, a command-line simulator using modified nodal analysis with transient analysis, and a Qt GUI with schematic editor, waveform viewer, project files and networking — plus a code-review report."
      },
      description: {
        fa: "این پروژه به‌صورت گروهی و در سه فاز انجام شد:\n\n- **فاز ۰، طراحی:** کلاس‌ها، نمودار UML، الگوهای طراحی (Factory، Bridge، MVC، Command)، روش‌های عددی و طراحی مدیریت خطا.\n- **فاز ۱، شبیه‌ساز خط فرمان:** دستورات به سبک LTspice و حل ماتریس MNA با کتابخانهٔ Eigen. عناصر پشتیبانی‌شده: مقاومت، خازن، سلف، دیود، منابع DC، سینوسی و پالسی، و منابع وابستهٔ E، G، H و F. تحلیل‌ها: گذرا (اویلر پسرو) و جاروب DC. منوی فایل برای ذخیره و بازکردن شماتیک‌ها هم دارد.\n- **فاز ۲، نسخهٔ گرافیکی با Qt 6 و ساختار MVC:** ویرایشگر شماتیک با کلید میانبر، چرخش و برچسب‌گذاری گره‌ها؛ نمایشگر شکل موج با زوم خودکار، تغییر مقیاس محورها، عملیات ریاضی روی سیگنال‌ها، کرسر و دابل کرسر؛ تحلیل گذرا، AC و فاز؛ تک‌قطبی‌ها، ذخیرهٔ پروژه با cereal و ارسال داده از طریق TCP.\n\n**بازبینی کد:** برای این صفحه، کد نهایی هر دو فاز دوباره کامپایل و آزمایش شد، بدون هیچ تغییری در کد.\n\n- **فاز ۱:** نتایج با ngspice مقایسه شد. حل‌کنندهٔ خطی برای مقاومت‌ها، منابع مستقل، منابع E، G و F و پاسخ گذرای مدارهای RC، RL و RLC درست و با دقت مرتبهٔ اول است.\n- **فاز ۲:** نسخهٔ گرافیکی زیر نمایشگر مجازی اجرا شد.\n- **کاستی‌ها:** مواردی مثل منبع H، سلف در تحلیل DC، دیود ایده‌آل و اتصال سیم‌ها در نسخهٔ گرافیکی کامل کار نمی‌کنند. همهٔ این موارد با علت و راه‌حل پیشنهادی در گزارش آمده است.",
        en: "A team project completed in three phases:\n\n- **Phase 0, design:** classes, UML, design patterns (Factory, Bridge, MVC, Command), numerical methods and an exception design.\n- **Phase 1, console simulator:** LTspice-style commands and an MNA solver built on Eigen. Elements: resistors, capacitors, inductors, diodes, DC/SIN/PULSE sources and E, G, H and F dependent sources. Analyses: backward-Euler transient and DC sweep. A file menu saves and opens schematics.\n- **Phase 2, Qt 6 GUI with an MVC layout:** a schematic editor with shortcuts, rotation and node labels; a waveform viewer with auto-zoom, axis scaling, math traces, a cursor and a double cursor; transient, AC and phase analyses; sub-circuits, cereal project files and TCP data transfer.\n\n**Code review:** for this page, the final code of both phases was rebuilt and tested without changing the code.\n\n- **Phase 1:** results were checked against ngspice. The linear solver is correct for resistors, independent sources, E/G/F sources and RC, RL and RLC transients, with the expected first-order accuracy.\n- **Phase 2:** the GUI was run under a virtual display.\n- **Gaps:** some parts do not fully work, including the H source, inductors in DC analysis, ideal diodes and wire connectivity in the GUI. Each is documented in the report with its cause and a suggested fix."
      },
      images: [
        { src: "assets/img/oop/rlc.webp", caption: { fa: "پاسخ پلهٔ مدار RLC سری: شبیه‌ساز فاز ۱ در مقایسه با ngspice", en: "Series RLC step response: Phase 1 simulator vs. ngspice" } },
        { src: "assets/img/oop/gui_charts.webp", caption: { fa: "نسخهٔ گرافیکی: ویرایشگر شماتیک و نمایشگر شکل موج (با سیگنال‌های نمونهٔ داخلی)", en: "Phase 2 GUI: schematic editor and waveform viewer (showing built-in sample traces)" } },
        { src: "assets/img/oop/gui_place.webp", caption: { fa: "قرار دادن المان‌ها با کلید میانبر و چرخش", en: "Placing components with shortcuts and rotation" } },
        { src: "assets/img/oop/ac.webp", caption: { fa: "تحلیل AC فیلتر RC پایین‌گذر با موتور تحلیل فاز ۲", en: "AC sweep of an RC low-pass with the Phase 2 engine" } }
      ],
      files: [
        { label: { fa: "گزارش بازبینی کد (PDF، انگلیسی)", en: "Code review report (PDF)" }, url: "projects/oop-circuit-simulator/report/oop_review.pdf" },
        { label: { fa: "گزارش طراحی فاز ۰ (PDF، فارسی)", en: "Phase 0 design document (PDF, Persian)" }, url: "projects/oop-circuit-simulator/report/phase0-design.pdf" }
      ],
      links: [
        { label: { fa: "کد نهایی فاز ۱ و ۲ در GitHub", en: "Final Phase 1 and Phase 2 code on GitHub" }, url: "https://github.com/seyedkiarash/seyedkiarash.github.io/tree/main/projects/oop-circuit-simulator" }
      ]
    },
    {
      id: "waveguide-field-visualizer",
      featured: true,
      title: {
        fa: "شبیه‌ساز سه‌بعدی میدان‌های الکترومغناطیسی در موجبرها و فیبر نوری",
        en: "3D Electromagnetic Field Visualizer for Waveguides and Optical Fibers"
      },
      year: { fa: "۱۴۰۵", en: "2026" },
      context: {
        fa: "تمرین کامپیوتری درس میدان‌ها و امواج — دکتر محمد معماریان",
        en: "Fields & Waves computer assignment — Dr. Mohammad Memarian"
      },
      tags: ["MATLAB", { fa: "الکترومغناطیس", en: "Electromagnetics" }, { fa: "شبیه‌سازی", en: "Simulation" }],
      cover: "assets/img/faw/figure1.webp",
      summary: {
        fa: "ابزاری در MATLAB که میدان‌های E و H را در موجبرهای صفحه‌موازی، مستطیلی و دایروی و در فیبر نوری به‌صورت سه‌بعدی و متحرک نمایش می‌دهد.",
        en: "A MATLAB tool that renders animated 3D E- and H-field distributions in parallel-plate, rectangular and circular waveguides and in optical fibers."
      },
      description: {
        fa: "**هدف:** ساخت یک شبیه‌ساز، مشابه شبیه‌سازهای رایج MATLAB، که مدهای اصلی انتشار در موجبرها و فیبر نوری را با تعریف پارامترهای فیزیکی محیط و شرایط اولیهٔ مناسب نمایش دهد.\n\n**عملکرد:** کاربر نوع ساختار، ابعاد هندسی، مشخصات محیط، فرکانس کاری و مد انتشار (TE یا TM) را انتخاب می‌کند. برنامه میدان‌ها را هم به‌صورت بردار و هم به‌صورت طیف اندازه، در سطح مقطع (تا ۲٫۵ برابر شعاع برای فیبر) و در امتداد محور انتشار (به طول سه طول‌موج) رسم می‌کند.\n\n- پشتیبانی از همهٔ مدهای TE و TM در موجبرهای صفحه‌موازی، مستطیلی و دایروی\n- پشتیبانی از مدهای TE₀ₙ و TM₀ₙ در فیبر نوری\n- نمایش سه‌بعدی و متحرک میدان‌ها با نرخ ۴۰ فریم بر ثانیه و مش‌بندی متراکم\n- منوی فارسی با امکان بازگشت به مرحلهٔ قبل\n- تشخیص مدهای ناموجود یا زیر فرکانس قطع و نمایش پیام خطا",
        en: "**Goal:** build a simulator, in the spirit of standard MATLAB-based tools, that visualizes the fundamental propagation modes of waveguides and optical fibers from the physical parameters of the medium and appropriate initial conditions.\n\n**How it works:** the user selects the structure, geometry, material parameters, operating frequency and propagation mode (TE or TM). The program renders the fields both as vector plots and as magnitude maps over the cross-section (up to 2.5× the core radius for fibers) and along the propagation axis (three wavelengths).\n\n- All TE and TM modes for parallel-plate, rectangular and circular waveguides\n- TE₀ₙ and TM₀ₙ modes for optical fibers\n- Animated 3D field plots at 40 fps on a dense spatial mesh\n- Persian-language menus with back-navigation between steps\n- Error handling for non-existent modes and modes below cutoff"
      },
      images: [
        { src: "assets/img/faw/figure1.webp", caption: { fa: "موجبر مستطیلی (a = 1 cm، b = 0.5 cm)، مد TE₁₁ در ۵۰ گیگاهرتز", en: "Rectangular waveguide (a = 1 cm, b = 0.5 cm), TE₁₁ mode at 50 GHz" } },
        { src: "assets/img/faw/figure2.webp", caption: { fa: "موجبر دایروی با شعاع ۱ سانتی‌متر، مد TM₂₁ در ۵۰ گیگاهرتز", en: "Circular waveguide, radius 1 cm, TM₂₁ mode at 50 GHz" } },
        { src: "assets/img/faw/figure3.webp", caption: { fa: "فیبر نوری (εr1 = 2، εr2 = 1.9)، مد TM₀₁ در ۵۰ گیگاهرتز", en: "Optical fiber (εr1 = 2, εr2 = 1.9), TM₀₁ mode at 50 GHz" } },
        { src: "assets/img/faw/figure4.webp", caption: { fa: "موجبر صفحه‌موازی (b = 10 cm)، مد TE₁ در ۲ گیگاهرتز", en: "Parallel-plate waveguide (b = 10 cm), TE₁ mode at 2 GHz" } }
      ],
      files: [
        { label: { fa: "گزارش پروژه (انگلیسی)", en: "Project report" }, url: "assets/files/faw/report.pdf" },
        { label: { fa: "کد MATLAB", en: "MATLAB code" }, url: "assets/files/faw/code.zip" }
      ],
      links: []
    },
    {
      id: "siren-notch-filter",
      featured: true,
      title: {
        fa: "جداسازی صدای گوینده از آژیر با فیلتر ناچ",
        en: "Separating Speech from a Siren Using Notch Filters"
      },
      year: { fa: "۱۴۰۵", en: "2026" },
      context: {
        fa: "پروژهٔ پایانی درس سیگنال‌ها و سیستم‌ها — دکتر آرش امینی",
        en: "Signals & Systems final project — Dr. Arash Amini"
      },
      tags: ["MATLAB", { fa: "پردازش سیگنال", en: "Signal Processing" }, { fa: "طراحی فیلتر", en: "Filter Design" }],
      cover: "assets/img/sas/spectrum-original.webp",
      summary: {
        fa: "طراحی فیلتر دیجیتال ناچ با جای‌گذاری صفر و قطب در صفحهٔ z برای حذف صدای آژیر از صدای یک مأمور پلیس.",
        en: "A digital notch filter, designed by pole–zero placement in the z-plane, that removes a siren from a recording of a police officer's speech."
      },
      description: {
        fa: "**مسئله:** در یک فایل صوتی، صدای یک مأمور پلیس با صدای آژیر ترکیب شده است. هدف، تضعیف صدای آژیر با حفظ هرچه بیشتر صدای گوینده است.\n\n**تحلیل طیف:** تبدیل فوریه با تقریب مجموع ریمانی روی نمونه‌های سیگنال محاسبه شد: `X(2πf) ≈ (1/Fs)·Σ x[k]·e^(−j2πfk/Fs)`. در طیف، صدای انسان پهن و هموار است و آژیر به‌صورت قله‌های باریک و تیز دیده می‌شود.\n\n**طراحی فیلتر:**\n- انتخاب ۸ قلهٔ تیز و پرانرژی طیف به‌عنوان فرکانس‌های آژیر\n- قرار دادن صفرها روی دایرهٔ واحد در همین فرکانس‌ها و قطب‌ها با همان زاویه و شعاع کمی کمتر از یک\n- پیاده‌سازی به‌صورت چهار فیلتر مرتبهٔ ۴ متوالی (در مجموع ۱۶ صفر و قطب) برای پایداری و دقت عددی بیشتر\n- r = 0.95 در فرکانس‌های بالا برای ناچ پهن‌تر و r = 0.975 در فرکانس‌های پایین برای حفظ فرمنت‌های صدا\n- عبور دوبارهٔ سیگنال از کل فیلتر برای تضعیف بیشتر\n\n**نتیجه:** صدای آژیر به‌شکل مؤثری تضعیف شد و صدای گوینده کمی خفه شد؛ تضعیف بیشتر آژیر ممکن بود اما صدای گوینده را بیش از حد تحریف می‌کرد.",
        en: "**Problem:** a recording of a police officer's speech is mixed with a siren. The goal is to suppress the siren while keeping as much of the voice as possible.\n\n**Spectral analysis:** the Fourier transform was evaluated numerically with a Riemann-sum approximation over the samples, `X(2πf) ≈ (1/Fs)·Σ x[k]·e^(−j2πfk/Fs)`. In the spectrum, the voice is broad and smooth, while the siren appears as sharp, narrow peaks.\n\n**Filter design:**\n- Picked the 8 sharpest, highest-energy peaks as the siren frequencies\n- Placed zeros on the unit circle at those frequencies and poles at the same angles just inside it\n- Implemented as four cascaded 4th-order sections (16 zeros and poles in total) for numerical stability\n- r = 0.95 at high frequencies for wider notches; r = 0.975 at low frequencies to protect the voice formants\n- Passed the signal through the full filter twice for extra attenuation\n\n**Result:** the siren is strongly attenuated with a slight muffling of the voice — further suppression was possible, but at the cost of making the speech hollow and distorted."
      },
      audio: [
        { src: "assets/audio/sas-original.mp3", caption: { fa: "صدای اصلی (گوینده + آژیر)", en: "Original (speech + siren)" } },
        { src: "assets/audio/sas-processed.mp3", caption: { fa: "خروجی فیلتر", en: "Filtered output" } }
      ],
      images: [
        { src: "assets/img/sas/spectrum-original.webp", caption: { fa: "تبدیل فوریهٔ سیگنال اصلی", en: "Fourier transform of the original signal" } },
        { src: "assets/img/sas/spectrum-processed.webp", caption: { fa: "تبدیل فوریهٔ سیگنال پس از فیلتر", en: "Fourier transform after filtering" } }
      ],
      files: [
        { label: { fa: "گزارش پروژه (انگلیسی)", en: "Project report" }, url: "assets/files/sas/report.pdf" },
        { label: { fa: "کد MATLAB", en: "MATLAB code" }, url: "assets/files/sas/code.zip" }
      ],
      links: []
    }
  ],

  /*
   * تمرین‌های کامپیوتری — نمایش فشرده در صفحهٔ پروژه‌ها و رزومه
   */
  assignments: [
    {
      title: { fa: "سیستم‌های LTI، تبدیل Z و پردازش تصویر", en: "LTI Stability, Z-Transform and Image Filtering" },
      course: { fa: "سیگنال‌ها و سیستم‌ها — دکتر آرش امینی", en: "Signals & Systems — Dr. Arash Amini" },
      term: { fa: "بهار ۱۴۰۵", en: "Spring 2026" },
      image: "assets/img/sas-hw/chw3-edges.webp",
      summary: {
        fa: "بررسی پایداری سیستم‌های پیوسته از روی قطب‌ها و پاسخ پله و ضربه، و اثر پارامتر میرایی بر پاسخ؛ نمودار صفر و قطب در صفحهٔ z، تعیین ناحیهٔ همگرایی و محاسبهٔ تبدیل Z معکوس با دو روش؛ تفکیک کانال‌های رنگی تصویر، مقایسهٔ rgb2gray با میانگین ساده، و یک سیستم تفاضلی به‌عنوان فیلتر بالاگذر برای آشکارسازی لبه.",
        en: "Stability of continuous-time systems from their poles and step/impulse responses, and the effect of the damping parameter; pole-zero plots in the z-plane, the region of convergence and the inverse Z-transform computed two ways; colour-channel analysis of an image, rgb2gray versus a plain average, and a differencing system used as a high-pass edge detector."
      },
      tags: ["MATLAB", { fa: "تبدیل Z", en: "Z-Transform" }, { fa: "پردازش تصویر", en: "Image Processing" }],
      files: [
        { label: { fa: "گزارش (PDF)", en: "Report (PDF)" }, url: "assets/files/sas-hw/CHW3-report.pdf" },
        { label: { fa: "کد MATLAB", en: "MATLAB code" }, url: "assets/files/sas-hw/CHW3-code.zip" }
      ]
    },
    {
      title: { fa: "محاسبات نمادین و تبدیل فوریه", en: "Symbolic Computation and Fourier Transforms" },
      course: { fa: "سیگنال‌ها و سیستم‌ها — دکتر آرش امینی", en: "Signals & Systems — Dr. Arash Amini" },
      term: { fa: "بهار ۱۴۰۵", en: "Spring 2026" },
      image: "assets/img/sas-hw/chw2-spectrum.webp",
      summary: {
        fa: "مسیر و سرعت یک پرتابه با ریاضیات نمادین MATLAB؛ طیف دامنه و فاز تبدیل فوریهٔ چند تابع و بررسی عددی خواص کانولوشن و ضرب در حوزهٔ زمان و فرکانس؛ اثر انتقال زمانی، مدولاسیون، تغییر مقیاس، مشتق‌گیری و ضرب در x بر تبدیل فوریه؛ و DFT سیگنال‌های گسسته و بخش‌های زوج و فرد آن‌ها.",
        en: "Projectile trajectory and velocity with MATLAB symbolic math; magnitude and phase spectra of several functions and a numerical check of the convolution and multiplication properties; how a time shift, modulation, time scaling, differentiation and multiplication by x change the Fourier transform; and the DFT of discrete signals and of their even and odd parts."
      },
      tags: ["MATLAB", { fa: "تبدیل فوریه", en: "Fourier Transform" }],
      files: [
        { label: { fa: "گزارش (PDF)", en: "Report (PDF)" }, url: "assets/files/sas-hw/CHW2-report.pdf" },
        { label: { fa: "کد MATLAB", en: "MATLAB code" }, url: "assets/files/sas-hw/CHW2-code.zip" }
      ]
    },
    {
      title: { fa: "سیگنال‌ها، کانولوشن و سری فوریه", en: "Signals, Convolution and Fourier Series" },
      course: { fa: "سیگنال‌ها و سیستم‌ها — دکتر آرش امینی", en: "Signals & Systems — Dr. Arash Amini" },
      term: { fa: "بهار ۱۴۰۵", en: "Spring 2026" },
      image: "assets/img/sas-hw/chw1-fourier.webp",
      summary: {
        fa: "رسم سیگنال‌های پیوسته و گسسته و مختلط (بخش حقیقی، موهومی، دامنه و فاز)؛ عملیات روی سیگنال و تجزیه به بخش زوج و فرد؛ نوشتن تابع کانولوشن و مقایسه با conv، و بررسی خواص کانولوشن؛ و محاسبهٔ تحلیلی ضرایب سری فوریه، بازسازی سیگنال با تعداد جملات مختلف، پدیدهٔ گیبس و همگرایی خطای MSE.",
        en: "Plotting continuous, discrete and complex signals (real/imaginary parts, magnitude and phase); signal operations and even/odd decomposition; a custom convolution function checked against conv and used to verify convolution properties; and analytically derived Fourier-series coefficients, reconstruction with an increasing number of terms, the Gibbs phenomenon and the convergence of the MSE."
      },
      tags: ["MATLAB", { fa: "سری فوریه", en: "Fourier Series" }, { fa: "کانولوشن", en: "Convolution" }],
      files: [
        { label: { fa: "گزارش (PDF)", en: "Report (PDF)" }, url: "assets/files/sas-hw/CHW1-report.pdf" },
        { label: { fa: "کد MATLAB", en: "MATLAB code" }, url: "assets/files/sas-hw/CHW1-code.zip" }
      ]
    },
    {
      title: { fa: "کاربردهای جبر خطی و بهینه‌سازی مقیددار", en: "Applied Linear Algebra & Constrained Optimization" },
      course: { fa: "روش‌های ریاضی در مهندسی — دکتر حسین پیل‌آرام", en: "Mathematical Methods in Engineering — Dr. Hossein Pilaram" },
      term: { fa: "بهار ۱۴۰۵", en: "Spring 2026" },
      image: "assets/img/mme/chw2-svd-rgb.webp",
      summary: {
        fa: "رتبه‌بندی PageRank با بردار ویژه، فضای پوچ و روش توانی؛ تحلیل رتبه و فضای پوچ ماتریس‌های یک شبکهٔ حسگر؛ فشرده‌سازی تصویر سیاه‌وسفید و رنگی با SVD و تحلیل حافظه (مثلاً k = 50 با حدود ۱۰٪ حافظه)؛ حل یک مسئلهٔ بهینه‌سازی مقیددار با شرایط KKT، روش جریمه (و بررسی بدحالتی آن) و روش لاگرانژ افزوده با خطای نهایی `1.8×10⁻⁶`؛ و تبدیل‌های هندسی دوبعدی با مختصات همگن در قالب یک شبیه‌سازی بازی ساده.",
        en: "PageRank via eigenvectors, null space and the power method; rank–nullity analysis of sensor-network matrices; SVD compression of grayscale and RGB images with storage analysis (e.g. k = 50 at ~10% storage); a constrained optimization problem solved with KKT conditions, the penalty method (including its ill-conditioning) and the augmented Lagrangian method (final error 1.8×10⁻⁶); and 2D transformations in homogeneous coordinates, wrapped in a small shooter-game simulation."
      },
      tags: ["Python", "SVD", { fa: "بهینه‌سازی", en: "Optimization" }],
      notebook: "assets/files/mme/CHW2.ipynb",
      download: "assets/files/mme/CHW2.zip"
    },
    {
      title: { fa: "پیاده‌سازی الگوریتم‌های جبر خطی از پایه", en: "Linear Algebra Algorithms from Scratch" },
      course: { fa: "روش‌های ریاضی در مهندسی — دکتر حسین پیل‌آرام", en: "Mathematical Methods in Engineering — Dr. Hossein Pilaram" },
      term: { fa: "بهار ۱۴۰۵", en: "Spring 2026" },
      image: "assets/img/mme/chw1-cauchy-schwarz.webp",
      summary: {
        fa: "پیاده‌سازی حذف گاوسی با محورگیری جزئی، روش گاوس–جردن (RREF)، وارون ماتریس، تشخیص هم‌ارزی سطری، دسته‌بندی جواب دستگاه‌های خطی، پایهٔ فضای پوچ و تجزیهٔ LDU با پایتون خالص و بدون کتابخانه، و اعتبارسنجی با NumPy و SciPy روی صدها ماتریس تصادفی. همچنین بررسی مونت‌کارلوی نامساوی کوشی–شوارتز در ابعاد مختلف و تصویر متعامد بردارها.",
        en: "Gaussian elimination with partial pivoting, Gauss–Jordan (RREF), matrix inversion, row-equivalence, classification of linear-system solutions, null-space bases and LDU decomposition — implemented in pure Python without libraries and validated against NumPy/SciPy on hundreds of random matrices. Also a Monte-Carlo study of the Cauchy–Schwarz ratio across dimensions, and orthogonal projections."
      },
      tags: ["Python", { fa: "جبر خطی", en: "Linear Algebra" }],
      notebook: "assets/files/mme/CHW1.ipynb",
      download: "assets/files/mme/CHW1.ipynb"
    },
    {
      title: { fa: "وابستگی غیرخطی، قانون اعداد بزرگ و قضیهٔ حد مرکزی", en: "Nonlinear Dependence, the Law of Large Numbers and the CLT" },
      course: { fa: "آمار و احتمال مهندسی — دکتر محمدحسین یاسایی", en: "Probability & Statistics — Dr. Mohammad Hossein Yassaee" },
      term: { fa: "پاییز ۱۴۰۴", en: "Fall 2025" },
      image: "assets/img/prob/chw2-dependence.webp",
      summary: {
        fa: "برای `Y = X² + ε` ضریب همبستگی پیرسون تقریباً صفر است (۰٫۰۵) در حالی که همبستگی فاصله‌ای حدود ۰٫۵ است؛ معیارهای وابستگی غیرخطی (همبستگی فاصله‌ای و HSIC) و تحلیل حساسیت به نویز و تعداد نمونه؛ همگرایی میانگین نمونه طبق قانون اعداد بزرگ و کاهش مربع خطای آن متناسب با `1/n`؛ و آزمون قضیهٔ حد مرکزی با تاس سالم و ناسالم.",
        en: "For Y = X² + ε the Pearson correlation is almost zero (0.05) while the distance correlation is about 0.5; nonlinear dependence measures (distance correlation, HSIC) and their sensitivity to noise and sample size; convergence of the sample mean by the law of large numbers with a mean squared error falling as 1/n; and the central limit theorem tested with fair and unfair dice."
      },
      tags: ["Python", { fa: "آمار", en: "Statistics" }, { fa: "شبیه‌سازی مونت‌کارلو", en: "Monte Carlo" }],
      notebook: "assets/files/prob/CHW2.ipynb",
      download: "assets/files/prob/CHW2.ipynb"
    },
    {
      title: { fa: "توزیع نمایی، پارادوکس روز تولد و جمع متغیرهای تصادفی", en: "Exponential Waiting Times, the Birthday Paradox and Sums of Random Variables" },
      course: { fa: "آمار و احتمال مهندسی — دکتر محمدحسین یاسایی", en: "Probability & Statistics — Dr. Mohammad Hossein Yassaee" },
      term: { fa: "پاییز ۱۴۰۴", en: "Fall 2025" },
      image: "assets/img/prob/chw1-birthday.webp",
      summary: {
        fa: "مدل‌سازی زمان انتظار با توزیع نمایی و مقایسهٔ احتمال‌های تحلیلی با شبیه‌سازی (مثلاً `P(X>10) = 0.135` در برابر `0.132` در شبیه‌سازی)؛ پارادوکس روز تولد با شبیه‌سازی و فرمول دقیق (۵۰٫۷٪ برای ۲۳ نفر)؛ برازش منحنی فراموشی نمایی به داده؛ و بررسی تجربی بسته بودن توزیع‌های نرمال، گاما و نمایی تحت جمع با معیار RMSE.",
        en: "Exponential waiting times with analytical probabilities checked by simulation (e.g. P(X>10) = 0.135 vs 0.132); the birthday paradox by simulation and the exact formula (50.7% for 23 people); fitting an exponential forgetting curve to data; and an experimental test, by RMSE, of whether normal, gamma and exponential distributions stay in their family under addition."
      },
      tags: ["Python", { fa: "احتمال", en: "Probability" }, { fa: "شبیه‌سازی مونت‌کارلو", en: "Monte Carlo" }],
      notebook: "assets/files/prob/CHW1.ipynb",
      download: "assets/files/prob/CHW1.ipynb"
    }
  ],

  activities: [
    {
      group: { fa: "پژوهش", en: "Research" },
      items: [
        {
          title: { fa: "همکار پژوهشی، آزمایشگاه چندرسانه‌ای", en: "Research Collaborator, Multimedia Lab" },
          org: { fa: "دانشکدهٔ مهندسی برق، دانشگاه صنعتی شریف — دکتر آرش امینی", en: "Department of Electrical Engineering, Sharif University of Technology — Dr. Arash Amini" },
          date: { fa: "", en: "" },
          description: { fa: "", en: "" }
        }
      ]
    },
    {
      group: { fa: "دستیار آموزشی", en: "Teaching Assistant" },
      items: [
        {
          title: { fa: "سردستیار آموزشی، تئوری مدار", en: "Head Teaching Assistant, Circuit Theory" },
          org: { fa: "دکتر روح‌الله امیری — دانشگاه صنعتی شریف", en: "Dr. Rouhollah Amiri — Sharif University of Technology" },
          date: { fa: "پاییز ۱۴۰۵", en: "Fall 2026" },
          description: { fa: "", en: "" }
        },
        {
          title: { fa: "دستیار آموزشی، آمار و احتمال", en: "Teaching Assistant, Probability & Statistics" },
          org: { fa: "دکتر محمدحسین یاسایی — دانشگاه صنعتی شریف", en: "Dr. Mohammad Hossein Yassaee — Sharif University of Technology" },
          date: { fa: "پاییز ۱۴۰۵", en: "Fall 2026" },
          description: { fa: "", en: "" }
        },
        {
          title: { fa: "سردستیار بخش تمرین، برنامه‌نویسی شیءگرا", en: "Head TA (Assignments), Object-Oriented Programming" },
          org: { fa: "دکتر عبدالله آراسته — دانشگاه صنعتی شریف", en: "Dr. Abdollah Arasteh — Sharif University of Technology" },
          date: { fa: "بهار ۱۴۰۵", en: "Spring 2026" },
          description: { fa: "", en: "" }
        },
        {
          title: { fa: "دستیار آموزشی، الکترومغناطیس", en: "Teaching Assistant, Electromagnetics" },
          org: { fa: "دکتر محمد معماریان — دانشگاه صنعتی شریف", en: "Dr. Mohammad Memarian — Sharif University of Technology" },
          date: { fa: "بهار ۱۴۰۵", en: "Spring 2026" },
          description: { fa: "", en: "" }
        },
        {
          title: { fa: "دستیار آموزشی، مبانی برنامه‌نویسی", en: "Teaching Assistant, Fundamentals of Programming" },
          org: { fa: "دکتر عبدالله آراسته — دانشگاه صنعتی شریف", en: "Dr. Abdollah Arasteh — Sharif University of Technology" },
          date: { fa: "پاییز ۱۴۰۴", en: "Fall 2025" },
          description: { fa: "", en: "" }
        }
      ]
    }
  ]
};
