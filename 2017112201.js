function isWordSubsequenceOfSequence(word, sequence) {
    let isCharacterAvailable = new Array(word.length)
    isCharacterAvailable.fill(false)
    let characterIndex = 0
    for (let i = 0; i < sequence.length; i++) {
        let s = sequence[i]
        let w = word[characterIndex]
        if (w === s) {
            isCharacterAvailable[characterIndex] = true
            characterIndex++
        }
    }
    for (let i = 0; i < isCharacterAvailable.length; i++) {
        if (!isCharacterAvailable[i]) {
            return false
        }
    }
    return true
}

function findLongestWordInWords(words) {
    let longestWord = ''
    for (let word of words) {
        if (longestWord.length < word.length) {
            longestWord = word
        }
    }
    return longestWord
}

const S = 'abppplee'
const D = ["able", "ale", "apple", "bale", "kangaroo"]

const subsequenceWords = D.filter(v => isWordSubsequenceOfSequence(v, S))
const longestSubsequenceWord = findLongestWordInWords(subsequenceWords)

console.log(longestSubsequenceWord)
