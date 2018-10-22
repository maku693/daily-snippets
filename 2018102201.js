(() => {
  const toggles = document.querySelectorAll('*[data-content-toggle]')
  const elements = Array.from(document.querySelectorAll(`*[data-content-lang]`))

  const elementsByLangs = elements.reduce((groups, element) => {
    const lang = element.getAttribute('data-content-lang')
    if (groups[lang] === undefined) {
      groups[lang] = []
    }
    groups[lang].push(element)
  }, {})

  for (const toggle of toggles) {
    toggle.addEventListener('change', e => {
      const lang = e.target.value
      for (const element of elementsByLangs[lang]) {
        element.setAttribute('hidden', 'hidden')
      }
    })
  }
})();
