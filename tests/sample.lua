local squares = {}
for i = 1, 10 do squares[i] = i * i end
-- Folded at compile time on the console: 1024 + 10.
squares.folded = 2^10 + 010
return squares
