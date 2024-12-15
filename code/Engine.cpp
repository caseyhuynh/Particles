#include "Engine.h"


using namespace std;


Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particle Window");
}

void Engine::run()
{
	Clock clock;
	Time time = clock.getElapsedTime();
	
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		Time time2 = clock.restart();
		float dt = time2.asSeconds();
		input();
		update(dt);
		draw();
	}
}

void Engine::input() {
	Event event;
	while (m_Window.pollEvent(event))
	{

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			for (int i = 0; i < 5; i++)
			{
				Vector2i position = Mouse::getPosition();
				int numPoints = 25 + rand() % (50 - 25 + 1);
				Particle p(m_Window, numPoints, position);
				m_particles.push_back(p); // 1:07 PM, I think we do this.
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Scan::Escape))
		{
			// right key is pressed: move our character
			m_Window.close();
		}

		if (event.type == Event::Closed)
			m_Window.close();
	}
}

void Engine::update(float dtAsSeconds) {
	vector<Particle>::iterator it;
	for (it = m_particles.begin(); it != m_particles.end(); it++)
	{
		if (it->getTTL() > 0.0)
		{
			it->update(dtAsSeconds);
		}
		else
		{
			it = m_particles.erase(it);
			break;
		}
	}
	
}

void Engine::draw() {
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();
}