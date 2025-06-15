require 'sfml'

# Структура для представления отрезка
Segment = Struct.new(:start, :end)

# Рекурсивная функция для генерации множества Кантора
def cantor_set(segments, start, end_, n, counter, max_depth)
  counter[0] += 1

  if counter[0] > max_depth
    puts "Превышена максимальная глубина рекурсии!"
    return
  end

  if n == 0
    segments << Segment.new(start, end_)
    return
  end

  length = end_ - start
  third1 = start + length / 3.0
  third2 = end_ - length / 3.0

  cantor_set(segments, start, third1, n - 1, counter, max_depth)
  cantor_set(segments, third2, end_, n - 1, counter, max_depth)
end

# Основная программа
puts "Введите количество итераций для множества Кантора: "
n = gets.chomp.to_i
max_depth = 1000

segments = []
recursion_counter = [0]
cantor_set(segments, 0.0, 1.0, n, recursion_counter, max_depth)

# Создаем окно для графического вывода
window = SFML::RenderWindow.new(SFML::VideoMode.new(800, 600), "Множество Кантора")
window.framerate_limit = 60

# Основной цикл отрисовки
while window.open?
  while event = window.poll_event
    if event.type == SFML::Event::Closed
      window.close
    end
  end

  window.clear(SFML::Color::White)

  # Рисуем отрезки множества Кантора
  y_pos = 50.0
  level_height = 50.0
  scale = 700.0 # Масштаб для визуализации

  (0..n).each do |level|
    # Находим все отрезки текущего уровня
    current_level = []
    temp_counter = [0]
    cantor_set(current_level, 0.0, 1.0, level, temp_counter, max_depth)

    # Рисуем отрезки текущего уровня
    current_level.each do |segment|
      line = SFML::RectangleShape.new
      line.size = SFML::Vector2.new((segment.end - segment.start) * scale, 5.0)
      line.position = SFML::Vector2.new(50 + segment.start * scale, y_pos)
      line.fill_color = SFML::Color::Black
      window.draw(line)
    end

    y_pos += level_height
  end

  window.display
end
