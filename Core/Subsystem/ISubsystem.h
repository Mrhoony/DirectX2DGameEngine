#pragma once

class ISubsystem
{
public:
	ISubsystem(class Context* context) : context(context) {};
	virtual ~ISubsystem() = default;

	virtual bool Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() {};

	const class Context* const GetContext() const { return context; }

private:
	class Context* context = nullptr;
};