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

  skills: [
    { group: { fa: "نرم‌افزار و ابزار", en: "Software & Tools" }, items: ["MATLAB", "LaTeX"] }
  ],

  projects: [
    {
      id: "waveguide-field-visualizer",
      featured: true,
      title: {
        fa: "شبیه‌ساز سه‌بعدی میدان‌های الکترومغناطیسی در موجبرها و فیبر نوری",
        en: "3D Electromagnetic Field Visualizer for Waveguides and Optical Fibers"
      },
      year: { fa: "۱۴۰۵", en: "2026" },
      context: {
        fa: "تمرین کامپیوتری درس میدان‌ها و امواج — دکتر معماریان",
        en: "Fields & Waves computer assignment — Dr. Memarian"
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
          org: { fa: "دانشگاه صنعتی شریف", en: "Sharif University of Technology" },
          date: { fa: "", en: "" },
          description: { fa: "", en: "" }
        },
        {
          title: { fa: "سردستیار بخش تمرین، برنامه‌نویسی شیءگرا", en: "Head TA (Assignments), Object-Oriented Programming" },
          org: { fa: "دانشگاه صنعتی شریف", en: "Sharif University of Technology" },
          date: { fa: "", en: "" },
          description: { fa: "", en: "" }
        },
        {
          title: { fa: "دستیار آموزشی، الکترومغناطیس", en: "Teaching Assistant, Electromagnetics" },
          org: { fa: "دانشگاه صنعتی شریف", en: "Sharif University of Technology" },
          date: { fa: "", en: "" },
          description: { fa: "", en: "" }
        },
        {
          title: { fa: "دستیار آموزشی، آمار و احتمال", en: "Teaching Assistant, Probability & Statistics" },
          org: { fa: "دانشگاه صنعتی شریف", en: "Sharif University of Technology" },
          date: { fa: "", en: "" },
          description: { fa: "", en: "" }
        },
        {
          title: { fa: "دستیار آموزشی، مبانی برنامه‌نویسی", en: "Teaching Assistant, Fundamentals of Programming" },
          org: { fa: "دانشگاه صنعتی شریف", en: "Sharif University of Technology" },
          date: { fa: "", en: "" },
          description: { fa: "", en: "" }
        }
      ]
    }
  ]
};
