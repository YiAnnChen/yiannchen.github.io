// Theme toggle (remembers the choice) and current-section highlighting in the top bar.
(function () {
  var r = document.documentElement, t = null;
  try { t = localStorage.getItem('ftec-theme'); } catch (e) {}
  if (!t) t = matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light';
  r.setAttribute('data-theme', t);
  document.addEventListener('DOMContentLoaded', function () {
    var b = document.querySelector('.theme');
    if (b) {
      var label = function () { b.textContent = r.getAttribute('data-theme') === 'dark' ? '淺色' : '深色'; };
      label();
      b.addEventListener('click', function () {
        var n = r.getAttribute('data-theme') === 'dark' ? 'light' : 'dark';
        r.setAttribute('data-theme', n); label();
        try { localStorage.setItem('ftec-theme', n); } catch (e) {}
      });
    }
    var links = Array.prototype.slice.call(document.querySelectorAll('.nav a[href^="#"]'));
    if (!links.length || !('IntersectionObserver' in window)) return;
    var io = new IntersectionObserver(function (es) {
      es.forEach(function (e) {
        if (!e.isIntersecting) return;
        links.forEach(function (a) {
          if (a.getAttribute('href') === '#' + e.target.id) a.setAttribute('aria-current', 'true');
          else a.removeAttribute('aria-current');
        });
      });
    }, { rootMargin: '-30% 0px -60% 0px' });
    links.forEach(function (a) { var s = document.querySelector(a.getAttribute('href')); if (s) io.observe(s); });
  });
})();
