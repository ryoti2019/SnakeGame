#pragma once
class StartMes
{
public:
	StartMes();
	~StartMes();
	bool Init(void);
	bool Update(void);
	bool Release(void);
	void Draw(void);
private:
	enum class Mes {
		Lady,
		Go,
		Max
	};
	int count;
	int imageHdl[static_cast<int>(Mes::Max)];
};

