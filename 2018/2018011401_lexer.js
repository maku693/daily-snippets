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
    const current = string[i]
    let isPushed = false
    if (current === tokens.comma) {
      scanned.push(buffer)
      scanned.push(current)
      isPushed = true
    }
    if (current === tokens.lineFeed) {
      scanned.push(buffer)
      isPushed = true
    }
    if (isPushed) {
      buffer = ''
      continue
    }

    buffer = buffer + current

    if (i === (string.length - 1)) {
      scanned.push(buffer)
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
  const test = (actual, expected) => {
    const isSucceeded = JSON.stringify(actual) === JSON.stringify(expected)
    console.log(`${isSucceeded ? 'ok' : 'fail'}`)
  }

  const testScan = () => {
    const actual = scan('abc,def')
    const expected = [ 'abc', ',', 'def' ]
    return test(actual, expected)
  }

  const testTokenize = () => {
    const actual = tokenize([ 'abc', ',', 'def' ])
    const expected = [
      { type: types.value, value: 'abc' },
      { type: types.separator, value: ',' },
      { type: types.value, value: 'def' },
    ]
    return test(actual, expected)
  }

  testScan()
  testTokenize()
})()

