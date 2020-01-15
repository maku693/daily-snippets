(() => {
  const toggles = document.querySelectorAll('data-content-toggle')
  for (const toggle of toggles) {
    toggle.addEventListener('change', e => {
      document.querySelectorAll(`data-content-lang=[${e.target.value}]`)
    })
  }
})();
