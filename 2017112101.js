const S = 'abppplee'
const D = ["able", "ale", "apple", "bale", "kangaroo"]

function isWordSubsequenceOfSequence(word, sequence) {
    let result = false
    let characterIndexForWord = 0
    for (let i = 0; i < sequence.length; i++) {
        let s = sequence[i]
        let w = word[characterIndexForWord]
        if (w === s) {
            characterIndexForWord++
        }
    }
}
