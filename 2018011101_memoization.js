'use strict';

function recursiveFib(v) {
  if (v === 0 || v === 1) {
    return v;
  }
  return recursiveFib(v - 2) + recursiveFib(v - 1);
}

function memoizedFib(v) {
  const results = [];
  for (let i = 0; i <= v; i++) {
    if (i === 0 || i === 1) {
      results.push(i);
    } else {
      results.push(results[i - 2] + results[i - 1]);
    }
  }
  return results[results.length - 1];
}

const count = 40;
const memoizedStarts = Date.now();
const memoized = memoizedFib(count);
console.log(`memoized: ${memoized} ${Date.now() - memoizedStarts}ms`);
const recursiveStarts = Date.now();
const recursive = recursiveFib(count);
console.log(`recursive: ${recursive} ${Date.now() - recursiveStarts}ms`);

