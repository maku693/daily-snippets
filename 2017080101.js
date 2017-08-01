(() => {

  const accessors = ['x', 'y', 'z', 'w']

  for (let i = 2; i <= 4; i++) {
    for (first of accessors) {
      for (second of accessors) {
        if (i == 2) {
          console.log(first + second)
          continue
        }

        for (third of accessors) {
          if (i == 3) {
            console.log(first + second + third)
            continue
          }

          for (fourth of accessors) {
            console.log(first + second + third + fourth)
          }
        }
      }
    }
  }

})()
