#include "Morph.h"
#include "BlinkLED.h"

template <typename T>
Morph<T>::Morph()
{
};

template <typename T>
Morph<T>::Morph(T min, T max, T v)
  : m_min(min)
  , m_max(max)
  , m_v(v)
  , m_cycles(0)
  , m_LED(NULL)
{
  m_current = getRandom(min, max);
  m_period = getRandom(min, max);
  m_direction = getRandom(0, 1) ? -1 : 1;
};
template <typename T>
void Morph<T>::setLED(BlinkLED* LED)
{
  m_LED = LED;
}

template <typename T>
T Morph<T>::update(const float dt)
{
  if( hitRoof() || hitFloor() )
    {
      m_direction = hitRoof() ? -1.0 : 1.0;
      if(m_LED)
	m_LED->setOnFor(100);
    }
  else if(m_cycles >= m_period)
    {
      m_period = getRandom((int)m_min, (int)m_max);
      m_cycles = 0;
    }
    
  m_current += m_direction * (T)getRandom((T)0, (T)m_v);
  m_cycles += 1;

  keepWithinBorders();

  return m_current;
    
};

template <typename T>
bool Morph<T>::hitRoof()
{
  return m_current >= m_max; 
}

template <typename T>
bool Morph<T>::hitFloor()
{
  return m_current <= m_min;
}

template <typename T>
void Morph<T>::keepWithinBorders()
{
  if( m_current > m_max )
    m_current = m_max;
 
  if( m_current < m_min )
      m_current = m_min;

}
template class Morph<int>;
template class Morph<float>;
