/*
 * ============================================================
 *  همهٔ محتوای سایت در همین فایل است.
 *  All site content lives in this file.
 * ============================================================
 *  - هر متن دوزبانه به شکل { fa: "...", en: "..." } نوشته می‌شود.
 *  - متن‌های بلند (bio, description) از قالب ساده پشتیبانی می‌کنند:
 *      **پررنگ**   [متن لینک](https://...)   خط خالی = پاراگراف جدید   "- " = فهرست
 *  - تصاویر را در assets/img و فایل‌ها (PDF، اسلاید، کد) را در assets/files بگذارید.
 *  - موارد علامت‌خورده با «نمونه» فقط برای نمایش قالب هستند و جایگزین می‌شوند.
 */

window.SITE = {
  defaultLang: "fa",

  profile: {
    name: { fa: "نام و نام خانوادگی", en: "Your Full Name" },
    title: {
      fa: "دانش‌آموختهٔ کارشناسی [رشته]، دانشگاه [نام دانشگاه]",
      en: "B.Sc. in [Field], [University Name]"
    },
    location: { fa: "تهران، ایران", en: "Tehran, Iran" },
    photo: "", // مثال: "assets/img/profile.jpg"
    bio: {
      fa: "این بخش معرفی کوتاه شماست: زمینه‌های مورد علاقه، آنچه در دوران دانشگاه انجام داده‌اید و هدف بعدی‌تان (ادامه تحصیل، کار، پژوهش).\n\nبا ارسال اطلاعات‌تان این متن جایگزین می‌شود.",
      en: "A short introduction: your interests, what you worked on during university, and what you are looking for next (graduate study, industry, research).\n\nThis text will be replaced with your own."
    },
    interests: {
      fa: ["زمینهٔ علاقه ۱", "زمینهٔ علاقه ۲", "زمینهٔ علاقه ۳"],
      en: ["Interest 1", "Interest 2", "Interest 3"]
    },
    email: "you@example.com",
    links: [
      { type: "github", label: "GitHub", url: "https://github.com/" },
      { type: "linkedin", label: "LinkedIn", url: "https://www.linkedin.com/" }
      // { type: "scholar", label: "Google Scholar", url: "..." },
      // { type: "orcid", label: "ORCID", url: "..." },
      // { type: "web", label: "Blog", url: "..." },
    ],
    cvPdf: { fa: "", en: "" } // مثال: { fa: "assets/files/cv-fa.pdf", en: "assets/files/cv-en.pdf" }
  },

  education: [
    {
      degree: { fa: "کارشناسی [رشته]", en: "B.Sc. in [Field]" },
      school: { fa: "دانشگاه [نام]", en: "[University Name]" },
      period: { fa: "۱۳۹۹ – ۱۴۰۳", en: "2020 – 2024" },
      gpa: { fa: "معدل: ۱۸٫۰۰ از ۲۰", en: "GPA: 18.00 / 20" },
      details: {
        fa: "پروژهٔ کارشناسی: [عنوان پروژه] — استاد راهنما: دکتر [نام]",
        en: "Thesis: [Project title] — Supervisor: Dr. [Name]"
      }
    }
  ],

  achievements: [
    {
      year: { fa: "۱۴۰۲", en: "2023" },
      title: { fa: "نمونه — رتبهٔ اول مسابقهٔ [نام]", en: "Sample — 1st place, [Competition]" },
      description: { fa: "توضیح کوتاه دربارهٔ این افتخار.", en: "A short note about this achievement." }
    },
    {
      year: { fa: "۱۴۰۱", en: "2022" },
      title: { fa: "نمونه — دانشجوی ممتاز ورودی", en: "Sample — Top student of the cohort" },
      description: { fa: "", en: "" }
    }
  ],

  skills: [
    { group: { fa: "برنامه‌نویسی", en: "Programming" }, items: ["Python", "C++", "MATLAB"] },
    { group: { fa: "ابزارها", en: "Tools" }, items: ["Git", "LaTeX", "Excel"] },
    { group: { fa: "زبان", en: "Languages" }, items: [{ fa: "فارسی (مادری)", en: "Persian (native)" }, { fa: "انگلیسی (پیشرفته)", en: "English (fluent)" }] }
  ],

  /*
   * پروژه‌ها — هر پروژه یک صفحهٔ جدا دارد: project.html?id=<id>
   * id فقط حروف انگلیسی، عدد و خط تیره.
   * featured: true  => در صفحهٔ اصلی هم نمایش داده می‌شود.
   */
  projects: [
    {
      id: "sample-course-project",
      featured: true,
      title: { fa: "نمونه — پروژهٔ درس [نام درس]", en: "Sample — [Course] Project" },
      year: { fa: "۱۴۰۲", en: "2023" },
      context: { fa: "پروژهٔ درسی — استاد: دکتر [نام]", en: "Course project — Instructor: Dr. [Name]" },
      role: { fa: "انفرادی", en: "Individual" },
      tags: ["Python", { fa: "پردازش داده", en: "Data Analysis" }],
      cover: "assets/img/sample-cover.svg",
      summary: {
        fa: "یک خط خلاصه دربارهٔ اینکه پروژه چه بود و چه نتیجه‌ای داشت.",
        en: "One-line summary of what the project was and what it achieved."
      },
      description: {
        fa: "**مسئله:** توضیح دهید چه مسئله‌ای را حل کردید.\n\n**روش:** چه کردید و از چه ابزارهایی استفاده شد.\n\n- نکتهٔ کلیدی اول\n- نکتهٔ کلیدی دوم\n\n**نتیجه:** دستاورد پروژه.",
        en: "**Problem:** describe what you set out to solve.\n\n**Approach:** what you did and which tools you used.\n\n- Key point one\n- Key point two\n\n**Result:** what came out of it."
      },
      images: [
        { src: "assets/img/sample-cover.svg", caption: { fa: "شرح تصویر", en: "Image caption" } }
      ],
      files: [
        // { label: { fa: "گزارش نهایی", en: "Final report" }, url: "assets/files/report.pdf" }
      ],
      links: [
        // { label: { fa: "کد در GitHub", en: "Code on GitHub" }, url: "https://github.com/..." }
      ]
    },
    {
      id: "sample-thesis",
      featured: true,
      title: { fa: "نمونه — پروژهٔ کارشناسی", en: "Sample — Bachelor's Thesis" },
      year: { fa: "۱۴۰۳", en: "2024" },
      context: { fa: "پروژهٔ پایانی — استاد راهنما: دکتر [نام]", en: "Final project — Supervisor: Dr. [Name]" },
      role: { fa: "پژوهشگر اصلی", en: "Lead researcher" },
      tags: [{ fa: "پژوهش", en: "Research" }, "MATLAB"],
      cover: "",
      summary: {
        fa: "خلاصهٔ پروژهٔ پایانی در یک یا دو جمله.",
        en: "A one- or two-sentence summary of the final project."
      },
      description: {
        fa: "توضیح کامل پروژه اینجا قرار می‌گیرد.",
        en: "The full project description goes here."
      },
      images: [],
      files: [],
      links: []
    }
  ],

  /*
   * فعالیت‌ها — هر گروه یک عنوان و چند مورد دارد.
   */
  activities: [
    {
      group: { fa: "دستیار آموزشی", en: "Teaching Assistant" },
      items: [
        {
          title: { fa: "نمونه — درس [نام درس]", en: "Sample — [Course name]" },
          org: { fa: "دانشگاه [نام]، دکتر [نام]", en: "[University], Dr. [Name]" },
          date: { fa: "پاییز ۱۴۰۲", en: "Fall 2023" },
          description: { fa: "", en: "" }
        }
      ]
    },
    {
      group: { fa: "کارگاه‌ها و دوره‌ها", en: "Workshops & Courses" },
      items: [
        {
          title: { fa: "نمونه — کارگاه [موضوع]", en: "Sample — [Topic] Workshop" },
          org: { fa: "برگزارکننده", en: "Organizer" },
          date: { fa: "۱۴۰۱", en: "2022" },
          description: { fa: "", en: "" }
        }
      ]
    },
    {
      group: { fa: "انجمن‌ها و فعالیت‌های دانشجویی", en: "Student Associations" },
      items: [
        {
          title: { fa: "نمونه — عضو انجمن علمی [رشته]", en: "Sample — Member, [Field] Scientific Association" },
          org: { fa: "دانشگاه [نام]", en: "[University]" },
          date: { fa: "۱۴۰۰ – ۱۴۰۲", en: "2021 – 2023" },
          description: { fa: "برگزاری رویداد [نام].", en: "Organized the [Name] event." }
        }
      ]
    }
  ]
};
