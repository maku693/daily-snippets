(() => {
  const main = () => {
    const canvas = document.getElementById('c')
    canvas.width = image.naturalWidth
    canvas.height = image.naturalHeight

    const ctx = canvas.getContext('2d')
    const src = ctx.createImageData(canvas.width, canvas.height)
    const dest = new ImageData(canvas.width, canvas.height)
    for (var x = 0; x < src.width; x++) {
    for (var y = 0; y < src.height; y++) {
      // TODO
      dest.data[x * y + 0] = 0.0
      dest.data[x * y + 1] = 0.0
      dest.data[x * y + 2] = 0.0
      dest.data[x * y + 3] = 1.0
    }
    }
    const blurred = blu
  }

  const image = document.createElement('img')
  image.src = 'image.png'
  image.onload = main
})()
