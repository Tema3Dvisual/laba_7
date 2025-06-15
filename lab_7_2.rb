MAX_RECURSION_DEPTH = 1000

def word_break(s, word_dict, depth = 0)
  if depth > MAX_RECURSION_DEPTH
    puts "Превышена максимальная глубина рекурсии!"
    return false
  end

  return true if s.empty?

  (1..s.length).each do |i|
    prefix = s[0...i]
    if word_dict.include?(prefix) && word_break(s[i..-1], word_dict, depth + 1)
      return true
    end
  end

  false
end

# Основная программа
print "Введите строку: "
s = gets.chomp

print "Введите слова словаря через пробел: "
dict = gets.chomp.split

result = word_break(s, dict)

puts "Результат: #{result}"
