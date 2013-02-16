#include "Morph.h"

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
  m_flip = (getRandom(0, 1) > 0);
};
template <typename T>
void Morph<T>::setLED(GPIOClass* LED)
{
  m_LED = LED;
}

template <typename T>
T Morph<T>::update()
{
  if(m_current >= m_max)
      m_flip = true;
  else if(m_current <= m_min)
    m_flip = false;
  else if(m_cycles >= m_period)
    {
      m_flip= !m_flip;
      m_period = getRandom((int)m_min, (int)m_max);
      m_cycles = 0;
    }
    
  float direction = m_flip ? -1.0 : 1.0;
  m_current += direction * (T)getRandom((T)0, (T)m_v);
  m_cycles += 1;

  return m_current;
    
};

template class Morph<int>;
template class Morph<float>;
