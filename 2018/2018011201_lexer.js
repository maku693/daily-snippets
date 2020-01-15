'use strict'

const tokens = {
  lineFeed: '\n',
  comma: ',',
}

const types = {
  value: Symbol(),
  separator: Symbol(),
}

const scan = (string) => {
  const scanned = []
  let buffer = ''
  for (let i = 0; i < string.length; i++) {
    let current = string[i]
    if (current === tokens.comma) {
      scanned.push(buffer)
      scanned.push(current)
      buffer = ''
      continue
    }
    buffer = buffer + current
    if (i === (string.length - 1) || current === tokens.lineFeed) {
      scanned.push(buffer)
      buffer = ''
    }
  }
  return scanned
}

const tokenize = (strings) => {
  return []
}

(() => {
  const deepEqualArray = (lhs, rhs) => {
    if (lhs.length != rhs.length) {
      return false
    }
    let same = false
    for (let i = 0; i < lhs.length; i++) {
      same = same || (lhs[i] === rhs[i])
    }
    return same
  }

  const testScan = () => {
    const actual = scan('abc,def')
    const expected = [ 'abc', ',', 'def' ]
    return deepEqualArray(actual, expected)
  }

  const testTokenize = () => {
    const actual = tokenize(scan('abc,def'))
    const expected = [
      {
        type: types.value,
        value: 'abc',
        position: { line: 1, column: 1 },
      },
      {
        type: types.separator,
        value: ',',
        position: { line: 1, column: 4 }
      },
      {
        type: types.value,
        value: 'def',
        position: { line: 1, column: 5 }
      },
    ]
    return actual === expected
  }

  const run = (test) => {
    console.log(`${test() ? 'ok' : 'fail'}`)
  }
  run(testScan)
  run(testTokenize)
})()

