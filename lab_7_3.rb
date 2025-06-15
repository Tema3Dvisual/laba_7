MAX_RECURSION_DEPTH = 1000

def can_place_items(items, containers, h, index = 0, depth = 0)
  if depth > MAX_RECURSION_DEPTH
    puts "Превышена максимальная глубина рекурсии!"
    return false
  end

  return true if index == items.size

  containers.each_with_index do |container, i|
    if container + items[index] <= h
      containers[i] += items[index]
      if can_place_items(items, containers, h, index + 1, depth + 1)
        return true
      end
      containers[i] -= items[index] # Бэктрекинг
    end
  end

  false
end

# Ввод данных
print "Введите количество контейнеров (N): "
n = gets.to_i
print "Введите высоту каждого контейнера (H): "
h = gets.to_i
print "Введите количество предметов: "
m = gets.to_i

puts "Введите высоты предметов (через пробел): "
items = gets.split.map(&:to_i).sort.reverse # Сортируем по убыванию

containers = Array.new(n, 0)

if can_place_items(items, containers, h)
  puts "Предметы можно разместить в контейнерах!"
else
  puts "Предметы нельзя разместить в контейнерах."
end
