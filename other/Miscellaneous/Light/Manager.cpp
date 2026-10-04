#include "Light/Manager.hpp"



void LightManager::Clear()
{
	Ambient_Count = 0;
	Solar_Count = 0;
	Point_Count = 0;
	Spot_Count = 0;
}

LightBase * LightManager::TakeAmbient()
{
	if (Ambient_Count < Ambient_Limit)
	{
		LightBase * light = &Ambient;
		Ambient_Count++;
		return light;
	}
	return nullptr;
}
LightDirection * LightManager::TakeDirection()
{
	if (Solar_Count < Solar_Limit)
	{
		LightDirection * light = &Solar;
		Solar_Count++;
		return light;
	}
	return nullptr;
}
LightPoint * LightManager::TakePoint()
{
	if (Point_Count < Point_Limit)
	{
		LightPoint * light = &Point_Array[Point_Count];
		Point_Count++;
		return light;
	}
	return nullptr;
}
LightSpot * LightManager::TakeSpot()
{
	if (Spot_Count < Spot_Limit)
	{
		LightSpot * light = &Spot_Array[Spot_Count];
		Spot_Count++;
		return light;
	}
	return nullptr;
}





#include "Light/BufferData.hpp"
LightBufferData LightManager::ToBufferData() const
{
	LightBufferData data;
	data.Ambient = Ambient;
	data.Solar = Solar;

	for (unsigned int i = 0; i < Point_Count; i++)
	{
		data.Point[i] = Point_Array[i];
	}
	data.PointCount = Point_Count;

	for (unsigned int i = 0; i < Spot_Count; i++)
	{
		data.Spot[i] = Spot_Array[i];
	}
	data.SpotCount = Spot_Count;

	return data;
}
