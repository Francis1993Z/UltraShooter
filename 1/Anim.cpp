#include "Anim.hpp"

Anim::Anim(void) : m_time()
{
	m_frameCount=0;
	m_delay=0.f;
	m_isLoop=true;
	m_play=true;
}

Anim::~Anim(void)
{
}

void Anim::nextFrame()
{
	if(currentFrame()==getSize()-1)
	{
			setFrame(0);
			if(!isLoop())
				stop();
	}
	else
		setFrame(currentFrame()+1);
}

void Anim::setFrame(const unsigned int &count)
{
	if(count<getSize())
		m_frameCount=count;
	else
		m_frameCount=0;
}

void Anim::reset()
{
	stop();
	play();
}

void Anim::loop(const bool &choice)
{
	m_isLoop=choice;
}

void Anim::play()
{
	m_play = true;
	m_time.Start();
}

void Anim::stop()
{
	Anim::m_play = false;
	setFrame(0);
	m_time.Reset();
	m_time.Pause();
}

void Anim::pause()
{
	Anim::m_play = false;
	m_time.Pause();
}

bool Anim::isPlaying() const
{
	return m_play;
}

void Anim::setDelay(const float &delay)
{
	m_delay=delay;
}

float Anim::delay() const
{
	return m_delay;
}

unsigned int Anim::currentFrame() const
{
	return m_frameCount;
}

bool Anim::isLoop() const
{
	return m_isLoop;
}

void Anim::update()
{
	if(isPlaying())
	{
		if(delay())
		{
			unsigned int frameCount = (unsigned int)(m_time.GetElapsedTime()/delay());
			if(!isLoop() && frameCount>getSize())
				stop();
			else
			{
				frameCount = frameCount % getSize();
				setFrame(frameCount);
			}
		}
		else nextFrame();
	}
}

