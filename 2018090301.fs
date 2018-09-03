let fizzbuzz x =
    if x % 3 == 0 then "fizz" else "" + if x % 5 == 0 then "buzz" else ""

let list = [for x in 1 .. 1000 do yield fizbuzz x]

println list
