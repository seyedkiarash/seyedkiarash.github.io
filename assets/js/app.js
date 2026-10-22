/* Rendering engine — normally you don't need to edit this file. */
(function () {
  "use strict";
  var S = window.SITE;
  var PAGE = document.body.getAttribute("data-page");

  /* ---------- language ---------- */
  function storeGet(k) { try { return localStorage.getItem(k); } catch (e) { return null; } }
  function storeSet(k, v) { try { localStorage.setItem(k, v); } catch (e) {} }
  var params = new URLSearchParams(location.search);
  var lang = params.get("lang");
  if (lang !== "fa" && lang !== "en") lang = storeGet("lang");
  if (lang !== "fa" && lang !== "en") lang = S.defaultLang || "fa";

  var UI = {
    home: { fa: "خانه", en: "Home" },
    projects: { fa: "پروژه‌ها", en: "Projects" },
    activities: { fa: "فعالیت‌ها", en: "Activities" },
    cv: { fa: "رزومه", en: "CV" },
    switchTo: { fa: "English", en: "فارسی" },
    about: { fa: "دربارهٔ من", en: "About" },
    education: { fa: "تحصیلات", en: "Education" },
    selected: { fa: "پروژه‌های منتخب", en: "Selected Projects" },
    allProjects: { fa: "همهٔ پروژه‌ها", en: "All projects" },
    achievements: { fa: "افتخارات و دستاوردها", en: "Honors & Achievements" },
    skills: { fa: "مهارت‌ها", en: "Skills" },
    interests: { fa: "علایق", en: "Interests" },
    contact: { fa: "ارتباط", en: "Contact" },
    downloadCv: { fa: "دریافت رزومه (PDF)", en: "Download CV (PDF)" },
    all: { fa: "همه", en: "All" },
    back: { fa: "بازگشت به پروژه‌ها", en: "Back to projects" },
    gallery: { fa: "تصاویر", en: "Images" },
    files: { fa: "فایل‌ها", en: "Files" },
    links: { fa: "پیوندها", en: "Links" },
    role: { fa: "نقش", en: "Role" },
    prev: { fa: "پروژهٔ قبلی", en: "Previous" },
    next: { fa: "پروژهٔ بعدی", en: "Next" },
    notFound: { fa: "این پروژه پیدا نشد.", en: "Project not found." },
    print: { fa: "چاپ / ذخیره به PDF", en: "Print / Save as PDF" },
    updated: { fa: "آخرین به‌روزرسانی", en: "Last updated" },
    projectsIntro: { fa: "پروژه‌های درسی، پژوهشی و شخصی دوران دانشگاه.", en: "Course, research and personal projects from my university years." },
    activitiesIntro: { fa: "فعالیت‌های آموزشی، دوره‌ها و همکاری‌های دانشجویی.", en: "Teaching, courses, and student activities." }
  };

  /* ---------- helpers ---------- */
  function t(x) {
    if (x == null) return "";
    if (typeof x === "object" && !Array.isArray(x)) {
      var v = x[lang];
      if (v == null || v === "") v = x.fa || x.en || "";
      return v;
    }
    return x;
  }
  function u(key) { return UI[key][lang]; }
  function esc(s) {
    return String(s).replace(/[&<>"']/g, function (c) {
      return { "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" }[c];
    });
  }
  function num(s) {
    s = String(s);
    return lang === "fa" ? s.replace(/[0-9]/g, function (d) { return "۰۱۲۳۴۵۶۷۸۹"[d]; }) : s;
  }
  function inline(s) {
    return esc(s)
      .replace(/\*\*(.+?)\*\*/g, "<strong>$1</strong>")
      .replace(/\[([^\]]+)\]\(([^)\s]+)\)/g, function (m, txt, url) {
        var ext = /^https?:/.test(url) ? ' target="_blank" rel="noopener"' : "";
        return '<a href="' + url + '"' + ext + ">" + txt + "</a>";
      });
  }
  function md(s) {
    s = t(s);
    if (!s) return "";
    return s.split(/\n\s*\n/).map(function (block) {
      var lines = block.split("\n");
      if (lines.every(function (l) { return /^\s*[-•]\s+/.test(l); })) {
        return "<ul>" + lines.map(function (l) { return "<li>" + inline(l.replace(/^\s*[-•]\s+/, "")) + "</li>"; }).join("") + "</ul>";
      }
      return "<p>" + lines.map(inline).join("<br>") + "</p>";
    }).join("");
  }
  function tagKey(tag) { return typeof tag === "object" ? (tag.en || tag.fa) : tag; }

  var ICONS = {
    email: '<path d="M4 6h16v12H4z" fill="none"/><path d="m4 7 8 6 8-6" fill="none"/>',
    github: '<path d="M9 19c-4 1.3-4-2-6-2.5M15 21v-3.5c0-1 .1-1.4-.5-2 2.8-.3 5.5-1.4 5.5-6a4.6 4.6 0 0 0-1.3-3.2 4.2 4.2 0 0 0-.1-3.2s-1-.3-3.4 1.3a11.7 11.7 0 0 0-6.2 0C6.6 2.8 5.6 3.1 5.6 3.1a4.2 4.2 0 0 0-.1 3.2A4.6 4.6 0 0 0 4.2 9.5c0 4.6 2.7 5.7 5.5 6-.6.6-.6 1.2-.5 2V21" fill="none"/>',
    linkedin: '<rect x="3" y="3" width="18" height="18" rx="2" fill="none"/><path d="M8 10v7M8 7v.01M12 17v-4a2 2 0 0 1 4 0v4M12 10v7" fill="none"/>',
    scholar: '<path d="m2 9 10-5 10 5-10 5z" fill="none"/><path d="M6 11v5c3 2 9 2 12 0v-5" fill="none"/>',
    orcid: '<circle cx="12" cy="12" r="9" fill="none"/><path d="M9 8v.01M9 11v6M13 11h1.5a3 3 0 0 1 0 6H13z" fill="none"/>',
    web: '<circle cx="12" cy="12" r="9" fill="none"/><path d="M3 12h18M12 3a14 14 0 0 1 0 18M12 3a14 14 0 0 0 0 18" fill="none"/>',
    file: '<path d="M14 3H6v18h12V7z" fill="none"/><path d="M14 3v4h4" fill="none"/>',
    download: '<path d="M12 4v11M7 10l5 5 5-5M5 20h14" fill="none"/>',
    location: '<path d="M12 21s-7-6.2-7-11a7 7 0 0 1 14 0c0 4.8-7 11-7 11z" fill="none"/><circle cx="12" cy="10" r="2.5" fill="none"/>',
    arrow: '<path d="M5 12h14M13 6l6 6-6 6" fill="none"/>'
  };
  function icon(name, cls) {
    return '<svg class="icon ' + (cls || "") + '" viewBox="0 0 24 24" aria-hidden="true">' + (ICONS[name] || ICONS.web) + "</svg>";
  }

  /* ---------- shell ---------- */
  function renderShell() {
    var html = document.documentElement;
    html.lang = lang;
    html.dir = lang === "fa" ? "rtl" : "ltr";
    var nav = [["home", "index.html"], ["projects", "projects.html"], ["activities", "activities.html"], ["cv", "cv.html"]];
    var active = PAGE === "project" ? "projects" : PAGE;
    document.getElementById("site-header").innerHTML =
      '<div class="wrap header-inner">' +
        '<a class="brand" href="index.html">' + esc(t(S.profile.name)) + "</a>" +
        '<nav class="nav" aria-label="main">' +
          nav.map(function (n) {
            return '<a href="' + n[1] + '"' + (active === n[0] ? ' aria-current="page"' : "") + ">" + u(n[0]) + "</a>";
          }).join("") +
          '<button class="lang-btn" type="button" id="lang-btn" lang="' + (lang === "fa" ? "en" : "fa") + '">' + u("switchTo") + "</button>" +
        "</nav>" +
      "</div>";
    document.getElementById("lang-btn").addEventListener("click", function () {
      var nl = lang === "fa" ? "en" : "fa";
      storeSet("lang", nl);
      var p = new URLSearchParams(location.search);
      p.set("lang", nl);
      location.search = p.toString();
    });
    document.getElementById("site-footer").innerHTML =
      '<div class="wrap footer-inner">' +
        "<span>© " + num(new Date().getFullYear()) + " " + esc(t(S.profile.name)) + "</span>" +
        '<span class="footer-links">' + contactLinks(true) + "</span>" +
      "</div>";
  }

  function contactLinks(compact) {
    var out = [];
    if (S.profile.email) out.push('<a href="mailto:' + esc(S.profile.email) + '" title="Email">' + icon("email") + (compact ? "" : "<span>" + esc(S.profile.email) + "</span>") + "</a>");
    (S.profile.links || []).forEach(function (l) {
      out.push('<a href="' + esc(l.url) + '" target="_blank" rel="noopener" title="' + esc(t(l.label)) + '">' + icon(l.type) + (compact ? "" : "<span>" + esc(t(l.label)) + "</span>") + "</a>");
    });
    return out.join("");
  }

  function cvButton() {
    var pdf = t(S.profile.cvPdf);
    if (!pdf) return "";
    return '<a class="btn" href="' + esc(pdf) + '" download>' + icon("download") + u("downloadCv") + "</a>";
  }

  function avatar(cls) {
    if (S.profile.photo) return '<img class="' + cls + '" src="' + esc(S.profile.photo) + '" alt="' + esc(t(S.profile.name)) + '">';
    var initials = t(S.profile.name).trim().split(/\s+/).slice(0, 2).map(function (w) { return w[0]; }).join("");
    return '<div class="' + cls + ' avatar-fallback" aria-hidden="true">' + esc(initials) + "</div>";
  }

  function tagsHtml(tags) {
    if (!tags || !tags.length) return "";
    return '<ul class="tags">' + tags.map(function (tg) { return '<li dir="auto">' + esc(t(tg)) + "</li>"; }).join("") + "</ul>";
  }

  function projectCard(p) {
    return '<a class="card" href="project.html?id=' + encodeURIComponent(p.id) + '">' +
      (p.cover ? '<div class="card-cover"><img src="' + esc(p.cover) + '" alt="" loading="lazy"></div>' : "") +
      '<div class="card-body">' +
        '<div class="meta">' + esc(t(p.year)) + (p.context ? " · " + esc(t(p.context)) : "") + "</div>" +
        "<h3>" + esc(t(p.title)) + "</h3>" +
        (p.summary ? "<p>" + inline(t(p.summary)) + "</p>" : "") +
        tagsHtml(p.tags) +
      "</div></a>";
  }

  function section(id, title, body, extra) {
    return '<section class="section" id="' + id + '"><div class="section-head"><h2>' + title + "</h2>" + (extra || "") + "</div>" + body + "</section>";
  }

  function entry(left, title, sub, desc) {
    return '<div class="entry"><div class="entry-date">' + esc(left || "") + '</div><div class="entry-main">' +
      "<h3>" + esc(title) + "</h3>" + (sub ? '<div class="entry-sub">' + esc(sub) + "</div>" : "") + (desc ? '<div class="entry-desc">' + md(desc) + "</div>" : "") +
      "</div></div>";
  }

  /* ---------- pages ---------- */
  function renderHome(main) {
    var P = S.profile;
    var interests = t(P.interests);
    var hero =
      '<section class="hero">' + avatar("hero-photo") +
        '<div class="hero-text">' +
          "<h1>" + esc(t(P.name)) + "</h1>" +
          '<p class="hero-title">' + esc(t(P.title)) + "</p>" +
          (P.location ? '<p class="hero-loc">' + icon("location") + esc(t(P.location)) + "</p>" : "") +
          '<div class="hero-links">' + contactLinks(false) + "</div>" +
          cvButton() +
        "</div>" +
      "</section>";
    var about = section("about", u("about"), '<div class="prose">' + md(P.bio) + "</div>" +
      (interests && interests.length ? '<div class="interests"><span class="label">' + u("interests") + ":</span>" + tagsHtml(interests) + "</div>" : ""));
    var edu = section("education", u("education"), (S.education || []).map(function (e) {
      var sub = [t(e.school), t(e.gpa)].filter(Boolean).join(" · ");
      return entry(t(e.period), t(e.degree), sub, e.details);
    }).join(""));
    var feat = (S.projects || []).filter(function (p) { return p.featured; });
    var projects = feat.length ? section("projects", u("selected"), '<div class="grid">' + feat.map(projectCard).join("") + "</div>",
      '<a class="more" href="projects.html">' + u("allProjects") + icon("arrow", "dir") + "</a>") : "";
    var ach = (S.achievements || []).length ? section("achievements", u("achievements"), (S.achievements).map(function (a) {
      return entry(t(a.year), t(a.title), "", a.description);
    }).join("")) : "";
    var skills = (S.skills || []).length ? section("skills", u("skills"), '<dl class="skills">' + S.skills.map(function (g) {
      return "<dt>" + esc(t(g.group)) + "</dt><dd>" + tagsHtml(g.items) + "</dd>";
    }).join("") + "</dl>") : "";
    main.innerHTML = hero + about + edu + projects + ach + skills;
    document.title = t(P.name);
  }

  function renderProjects(main) {
    var all = S.projects || [];
    var tags = [], seen = {};
    all.forEach(function (p) { (p.tags || []).forEach(function (tg) { var k = tagKey(tg); if (!seen[k]) { seen[k] = 1; tags.push(tg); } }); });
    var current = params.get("tag") || "";
    function draw() {
      var list = all.filter(function (p) { return !current || (p.tags || []).some(function (tg) { return tagKey(tg) === current; }); });
      document.getElementById("project-list").innerHTML = list.map(projectCard).join("");
      Array.prototype.forEach.call(document.querySelectorAll(".filter button"), function (b) {
        b.setAttribute("aria-pressed", b.getAttribute("data-tag") === current ? "true" : "false");
      });
    }
    main.innerHTML =
      '<header class="page-head"><h1>' + u("projects") + "</h1><p>" + u("projectsIntro") + "</p></header>" +
      (tags.length > 1 ? '<div class="filter" role="group">' +
        '<button type="button" data-tag="">' + u("all") + "</button>" +
        tags.map(function (tg) { return '<button type="button" data-tag="' + esc(tagKey(tg)) + '">' + esc(t(tg)) + "</button>"; }).join("") +
      "</div>" : "") +
      '<div class="grid" id="project-list"></div>';
    Array.prototype.forEach.call(main.querySelectorAll(".filter button"), function (b) {
      b.addEventListener("click", function () { current = b.getAttribute("data-tag"); draw(); });
    });
    draw();
    document.title = u("projects") + " — " + t(S.profile.name);
  }

  function renderProject(main) {
    var all = S.projects || [];
    var id = params.get("id");
    var idx = -1;
    all.forEach(function (p, i) { if (p.id === id) idx = i; });
    var back = '<a class="back" href="projects.html">' + icon("arrow", "dir back-icon") + u("back") + "</a>";
    if (idx < 0) { main.innerHTML = back + '<p class="empty">' + u("notFound") + "</p>"; return; }
    var p = all[idx];
    var meta = [t(p.year), t(p.context)].filter(Boolean).map(esc).join(" · ");
    var html = back +
      '<article class="project">' +
        '<header class="page-head"><div class="meta">' + meta + "</div><h1>" + esc(t(p.title)) + "</h1>" +
          (p.role ? '<div class="meta">' + u("role") + ": " + esc(t(p.role)) + "</div>" : "") +
          tagsHtml(p.tags) + "</header>" +
        (p.cover ? '<figure class="project-cover"><img src="' + esc(p.cover) + '" alt=""></figure>' : "") +
        '<div class="prose">' + md(p.description || p.summary) + "</div>";
    var imgs = (p.images || []).filter(function (im) { return im.src !== p.cover; });
    if (imgs.length) {
      html += '<h2 class="sub-h">' + u("gallery") + '</h2><div class="gallery">' + imgs.map(function (im) {
        return '<figure><a href="' + esc(im.src) + '" target="_blank" rel="noopener"><img src="' + esc(im.src) + '" alt="' + esc(t(im.caption)) + '" loading="lazy"></a>' +
          (im.caption ? "<figcaption>" + esc(t(im.caption)) + "</figcaption>" : "") + "</figure>";
      }).join("") + "</div>";
    }
    if ((p.files || []).length) {
      html += '<h2 class="sub-h">' + u("files") + '</h2><ul class="file-list">' + p.files.map(function (f) {
        var ext = (f.url.split(".").pop() || "").toUpperCase();
        return '<li><a href="' + esc(f.url) + '" target="_blank" rel="noopener">' + icon("file") + "<span>" + esc(t(f.label)) + "</span>" +
          (ext.length <= 4 ? '<span class="ext">' + esc(ext) + "</span>" : "") + "</a></li>";
      }).join("") + "</ul>";
    }
    if ((p.links || []).length) {
      html += '<h2 class="sub-h">' + u("links") + '</h2><ul class="file-list">' + p.links.map(function (l) {
        var ic = /github\.com/.test(l.url) ? "github" : "web";
        return '<li><a href="' + esc(l.url) + '" target="_blank" rel="noopener">' + icon(ic) + "<span>" + esc(t(l.label)) + "</span></a></li>";
      }).join("") + "</ul>";
    }
    var prev = all[idx - 1], next = all[idx + 1];
    html += '<nav class="pager">' +
      (prev ? '<a href="project.html?id=' + encodeURIComponent(prev.id) + '"><small>' + u("prev") + "</small>" + esc(t(prev.title)) + "</a>" : "<span></span>") +
      (next ? '<a class="pager-next" href="project.html?id=' + encodeURIComponent(next.id) + '"><small>' + u("next") + "</small>" + esc(t(next.title)) + "</a>" : "<span></span>") +
      "</nav></article>";
    main.innerHTML = html;
    document.title = t(p.title) + " — " + t(S.profile.name);
  }

  function renderActivities(main) {
    main.innerHTML = '<header class="page-head"><h1>' + u("activities") + "</h1><p>" + u("activitiesIntro") + "</p></header>" +
      (S.activities || []).map(function (g, i) {
        return section("g" + i, esc(t(g.group)), g.items.map(function (it) {
          return entry(t(it.date), t(it.title), t(it.org), it.description);
        }).join(""));
      }).join("");
    document.title = u("activities") + " — " + t(S.profile.name);
  }

  function renderCv(main) {
    var P = S.profile;
    var contact = [S.profile.email].concat((P.links || []).map(function (l) { return l.url.replace(/^https?:\/\/(www\.)?/, "").replace(/\/$/, ""); })).filter(Boolean);
    var html = '<div class="cv-actions">' + cvButton() + '<button type="button" class="btn btn-ghost" onclick="window.print()">' + u("print") + "</button></div>" +
      '<article class="cv">' +
        '<header class="cv-head"><h1>' + esc(t(P.name)) + "</h1><p>" + esc(t(P.title)) + "</p>" +
        '<p class="cv-contact">' + [t(P.location)].concat(contact).filter(Boolean).map(function (c) { return "<span>" + esc(c) + "</span>"; }).join("") + "</p></header>";
    function cvSec(title, body) { return body ? '<section class="cv-sec"><h2>' + title + "</h2>" + body + "</section>" : ""; }
    html += cvSec(u("education"), (S.education || []).map(function (e) {
      return entry(t(e.period), t(e.degree), [t(e.school), t(e.gpa)].filter(Boolean).join(" · "), e.details);
    }).join(""));
    html += cvSec(u("projects"), (S.projects || []).map(function (p) {
      return entry(t(p.year), t(p.title), t(p.context), p.summary);
    }).join(""));
    html += cvSec(u("achievements"), (S.achievements || []).map(function (a) { return entry(t(a.year), t(a.title), "", a.description); }).join(""));
    (S.activities || []).forEach(function (g) {
      html += cvSec(esc(t(g.group)), g.items.map(function (it) { return entry(t(it.date), t(it.title), t(it.org), it.description); }).join(""));
    });
    html += cvSec(u("skills"), '<dl class="skills">' + (S.skills || []).map(function (g) {
      return "<dt>" + esc(t(g.group)) + "</dt><dd>" + (g.items || []).map(function (x) { return '<bdi>' + esc(t(x)) + "</bdi>"; }).join(lang === "fa" ? "، " : ", ") + "</dd>";
    }).join("") + "</dl>");
    html += "</article>";
    main.innerHTML = html;
    document.title = u("cv") + " — " + t(P.name);
  }

  renderShell();
  var main = document.getElementById("app");
  ({ home: renderHome, projects: renderProjects, project: renderProject, activities: renderActivities, cv: renderCv }[PAGE] || renderHome)(main);
})();
