#include <SFML/Graphics.hpp>
#include <optional>

// Объявление констант
constexpr unsigned ANTIALIASING_LEVEL = 8;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned MAX_FPS = 60;

// Предварительно объявление функции
void createWindow(sf::RenderWindow& window);
void initializePacman(sf::CircleShape& shape);
void handleEvents(sf::RenderWindow& window);
void update(sf::Clock& clock, sf::CircleShape& shape);
void render(sf::RenderWindow& window, sf::CircleShape& shape);

// Определение функций
// Создание окна приложения
void createWindow(sf::RenderWindow& window)
{
    sf::ContextSettings settings;
    settings.antiAliasingLevel = ANTIALIASING_LEVEL;
    window.create(
        sf::VideoMode( {WINDOW_WIDTH, WINDOW_HEIGHT} ),
        "PacMan Clone", sf::Style::Default,
        sf::State::Windowed, settings
    );
    window.setFramerateLimit(MAX_FPS);
}

// Инициализация фигуры пакмана
void initializePacman(sf::CircleShape& shape)
{
    shape.setRadius(20.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({100.f, 0.f});
}

// Обрабатываем все события, скопившиеся в очереди событий sfml
void handleEvents(sf::RenderWindow& window)
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
    }
}

// Обновление фигуры пакмана
void update(sf::Clock& clock, sf::CircleShape& shape)
{
    const sf::Vector2f speed = { 200.f, 0.f };

    const float elapsedSeconds = clock.restart().asSeconds();
    shape.setPosition(shape.getPosition() + speed * elapsedSeconds);
}

// Рисуем фигуру пакмана
void render(sf::RenderWindow& window, sf::CircleShape& shape)
{
    window.clear(sf::Color::Black);
    window.draw(shape);
    window.display();
}

int main()
{
    sf::RenderWindow window;
    createWindow(window);

    sf::CircleShape pacman;
    initializePacman(pacman);

    sf::Clock clock;
    while (window.isOpen())
    {
        handleEvents(window);
        update(clock, pacman);
        render(window, pacman);
    }

    return 0;
}