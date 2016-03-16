#pragma once

class IDestroyable
{
public:
	virtual bool IsDestroyed()
	{
		return bDestroy;
	}
	virtual void Destroy()
	{
		bDestroy = true;
	}
private:
	bool bDestroy;
};
