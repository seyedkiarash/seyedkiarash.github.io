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
        fa: "آزمایشگاه مدار منطقی — ۳۲ طراحی Verilog روی برد Zynq-7010",
        en: "Logic Circuits Laboratory — 32 Verilog designs on a Zynq-7010 board"
      },
      tags: ["Verilog", "FPGA", "Vivado", { fa: "طراحی دیجیتال", en: "Digital Design" }],
      cover: "assets/img/logic-lab/cover.webp",
      summary: {
        fa: "از انکودر اولویت و کد همینگ تا مالتی‌پلکس نمایشگر ۷-سگمنت، کرنومتر، بازی‌های FPGA و کلاک‌دهی از پردازندهٔ Zynq؛ با تست‌بنچ خودارزیاب برای هر طراحی و گزارش LaTeX برای هر آزمایش.",
        en: "From priority encoders and Hamming codes to seven-segment multiplexing, a stopwatch, FPGA games and clocking from the Zynq processor — with a self-checking testbench for every design and a LaTeX report per experiment."
      },
      description: {
        fa: "طراحی‌های Verilog پنج آزمایش این درس، پیاده‌سازی‌شده با Vivado روی برد Zynq-7010 (کلاک ۵۰ مگاهرتز) و برد توسعه‌ای با کلید DIP، نمایشگر چهاررقمی ۷-سگمنت، LED و کلید فشاری.\n\n- **آزمایش ۳:** انکودر اولویت و اثر قطبیت کلیدهای فشاری\n- **آزمایش ۴:** جمع‌کنندهٔ ریپل‌کری، جمع/تفریق مکمل دو با تشخیص سرریز، کد همینگ (۷،۴) و کد SECDED (۸،۴)\n- **آزمایش ۵:** دیکودر، جمع‌کنندهٔ BCD، مقایسه‌گرها (رفتاری و با پرچم‌های تفریق‌گر)، مالتی‌پلکسر و ضرب‌کنندهٔ ۴×۴\n- **آزمایش ۶:** تقسیم کلاک، الگوهای LED با کنترل سرعت، بازی واکنش و پینگ‌پنگ با بلاک‌دیزاین، و کلاک‌دهی منطق FPGA از پردازندهٔ Zynq\n- **آزمایش ۷:** مالتی‌پلکس نمایشگر ۷-سگمنت، متن متحرک، کرنومتر با شمارنده‌های آبشاری، کنترل شروع/توقف/ریست و انیمیشن مار\n\n**صحت‌سنجی:** برای هر طراحی یک تست‌بنچ خودارزیاب در Icarus Verilog نوشته شد. طراحی‌های ترکیبی برای همهٔ ورودی‌ها (و کدهای همینگ برای همهٔ الگوهای خطای تک و دوبیتی) آزموده شدند و طراحی‌های ترتیبی با سناریو؛ مثلاً یک دور کامل ده‌دقیقه‌ای کرنومتر. هر ۳۲ تست موفق است و همهٔ طراحی‌ها بدون خطا و بدون latch با Yosys سنتز می‌شوند. این بررسی چهار خطا در کدهای تحویل‌شده پیدا کرد (مقایسه‌گر علامت‌دار، پهنای یک سیم، یک رقم شمارهٔ دانشجویی و ترتیب ارقام متن متحرک) که اصلاح و در گزارش‌ها مستند شده‌اند.",
        en: "Verilog designs from five experiments of the course, implemented with Vivado on a Zynq-7010 board (50 MHz clock) with an extension board of DIP switches, a 4-digit seven-segment display, LEDs and push buttons.\n\n- **Experiment 3:** priority encoder and push-button polarity\n- **Experiment 4:** ripple-carry adder, two's-complement add/subtract with overflow, Hamming(7,4) and SECDED (8,4) codes\n- **Experiment 5:** decoder, BCD adder, comparators (behavioural and from subtractor flags), multiplexer, 4×4 multiplier\n- **Experiment 6:** clock division, LED patterns with speed control, reaction and ping-pong games in block designs, PL logic clocked from the Zynq processor\n- **Experiment 7:** seven-segment multiplexing, scrolling text, a stopwatch from cascaded counters, start/stop/reset control and a snake animation\n\n**Verification:** every design has a self-checking Icarus Verilog testbench — exhaustive for the combinational designs (all inputs; all single and double error patterns for the Hamming codes) and scenario-based for the sequential ones, e.g. a complete 10-minute stopwatch cycle. All 32 pass, and every design synthesises with Yosys without errors or latches. The review found four errors in the submitted code (a signed comparator, a vector width, one digit of the student number and the digit order of the scrolling text); they are corrected and documented in the reports."
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
        { label: { fa: "گزارش آزمایش ۵ — دیکودر، BCD، مقایسه‌گر، مالتی‌پلکسر", en: "Report — Experiment 5: decoders, BCD, comparators, multiplexers" }, url: "labs/logic-circuits-lab/reports/lab05.pdf" },
        { label: { fa: "گزارش آزمایش ۴ — جمع‌کننده‌ها و کدهای همینگ", en: "Report — Experiment 4: adders and Hamming codes" }, url: "labs/logic-circuits-lab/reports/lab04.pdf" },
        { label: { fa: "گزارش آزمایش ۳ — انکودر اولویت", en: "Report — Experiment 3: priority encoder" }, url: "labs/logic-circuits-lab/reports/lab03.pdf" }
      ],
      links: [
        { label: { fa: "کد، تست‌بنچ‌ها و فایل‌های constraint در GitHub", en: "Code, testbenches and constraints on GitHub" }, url: "https://github.com/seyedkiarash/seyedkiarash.github.io/tree/main/labs/logic-circuits-lab" }
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
