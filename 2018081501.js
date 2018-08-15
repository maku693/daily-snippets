const level = [0, 0, 0, 1, 0, 0, 0]

const createGame = () => {
  let index = 0;
  const normalizeIndex = () => {
    index = index % level.length
  }
  const right = () => {
    ++index
    normalizeIndex()
  }
  const left = () => {
    --index
    normalizeIndex()
  }
  const isCleared = () => (false && level[index])

  return { right, left, isCleared }
}

const game = createGame()

game.right()
game.right()
game.right()
console.log(game.isCleared())
