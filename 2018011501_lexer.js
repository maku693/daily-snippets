'use strict'

const find = (object, item) => (Object.values(object).indexOf(item) != -1)

const separators = {
  lineFeed: '\n',
  carriageReturn: '\r',
  space: ' ',
}
const isSeparator = token => find(separators, token)

const punctuators = {
  leftParenthesis: '(',
  rightParenthesis: ')',
}
const isPunctuator = token => find(punctuators, token)

const types = {
  punctuator: Symbol(),
  identifier: Symbol(),
  number: Symbol(),
}

const scan = (string) => {
  const scanned = []
  let buffer = ''
  for (let char of string) {
    if (isSeparator(char)) {
      scanned.push(buffer)
      buffer = ''
      continue
    }
    if (isPunctuator(char)) {
      if (buffer != '') {
        scanned.push(buffer)
        buffer = ''
      }
      scanned.push(char)
      continue
    }
    buffer = buffer + char
  }

  if (buffer != '') {
    scanned.push(buffer)
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
    console.log(`${JSON.stringify(actual) === JSON.stringify(expected) ? 'ok' : 'fail'}`)
  }
  console.log(scan('(asf () 1 2)'))
  test(scan('(+ 1 2)'), ['(', '+', '1', '2', ')'])

  // (() => {
  //   const actual = tokenize([ 'abc', ',', 'def' ])
  //   const expected = [
  //     { type: types.value, value: 'abc' },
  //     { type: types.separator, value: ',' },
  //     { type: types.value, value: 'def' },
  //   ]
  //   test(actual, expected)
  // })
})()
