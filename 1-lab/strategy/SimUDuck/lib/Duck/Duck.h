#ifndef DUCK_H
#define DUCK_H

#include "Fly/IFlyBehavior.h"
#include "Quack/IQuakBehavior.h"
#include "Dance/IDanceBehavior.h"
#include "Quack/MuteQuackBehavior.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

class Duck
{
public:
	Duck(std::unique_ptr<IFlyBehavior> &&flyBehavior,
	     std::unique_ptr<IQuackBehavior> &&quackBehavior,
	     std::unique_ptr<IDanceBehavior> &&danceBehavior)
	//&& - r-value ссылка (разрешает только перемещение, а не копирование)

		: m_quackBehavior(std::move(quackBehavior)),
		  m_danceBehavior(std::move(danceBehavior))
	{
		assert(m_quackBehavior);
		assert(m_danceBehavior);
		SetFlyBehavior(std::move(flyBehavior));
	}

	//Параметр flyBehavior → [nullptr]
	//Поле m_flyBehavior → [указатель на стратегию]

	void Quack() const
	{
		m_quackBehavior->Quack();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		m_flyBehavior->Fly();

		if (CanQuack()  && !m_flyBehavior
			// && m_flyBehavior->GetFlightCount() != 0
			// && m_flyBehavior->GetFlightCount() % 2 == 0
			)
		{
			std::cout << "COOL " ;
			m_quackBehavior->Quack();

		}
	}

	virtual void Dance()
	{
		m_danceBehavior->Dance();
	}

	void SetFlyBehavior(std::unique_ptr<IFlyBehavior> &&flyBehavior)
	{
		assert(flyBehavior);
		m_flyBehavior = std::move(flyBehavior);
	}

	void SetDanceBehavior(std::unique_ptr<IDanceBehavior> &&danceBehavior)
	{
		assert(danceBehavior);
		m_danceBehavior = std::move(danceBehavior);
	}

	bool CanQuack()
	{
		if (!m_quackBehavior) return false;
		return dynamic_cast<MuteQuackBehavior *>(m_quackBehavior.get()) == nullptr;

		//проверка является ли m_quackBehavior - std::unique_ptr<IQuackBehavior>
		//типа std::unique_ptr <MuteQuackBehavior*>
	}

	virtual void Display() const = 0;

	virtual ~Duck() = default;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

#endif
