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
  const result = []
  for (let string of strings) {
    let type
    switch (string) {
    case tokens.comma:
      type = types.separator
    default:
      type = types.token
    }
    result.push({ type: type, value: string })
  }
  return result
}

(() => {
  const deepEqual = (lhs, rhs) =>
    (JSON.stringify(lhs) === JSON.stringify(rhs))

  const run = (test) => {
    console.log(`${test() ? 'ok' : 'fail'}`)
  }

  const testScan = () => {
    const actual = scan('abc,def')
    const expected = [ 'abc', ',', 'def' ]
    return deepEqual(actual, expected)
  }

  const testTokenize = () => {
    const actual = tokenize([ 'abc', ',', 'def' ])
    const expected = [
      { type: types.value, value: 'abc' },
      { type: types.separator, value: ',' },
      { type: types.value, value: 'def' },
    ]
    return deepEqual(actual, expected)
  }

  run(testScan)
  run(testTokenize)
})()

