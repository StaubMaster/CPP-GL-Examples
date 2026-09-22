#include "AuxThread/AuxThread0.hpp"

#include "Telemetry/StopWatch.hpp"

#include "ContextNoisePlane.hpp"



AuxThread0::AuxThread0(ContextNoisePlane & context)
	: AuxThreadBase("AuxThread0")
	, Context(context)
{ }



bool AuxThread0::CheckFunc()
{
	return true;
}
void AuxThread0::DoFunc()
{
	StopWatch sw;
	//while (!Term)
	{
		//if (!DoIdle)
		{
			sw.Clear(); sw.Start();
			//Context.ChunkManager.Container.ChangeCenter((Context.View.Trans.Position / (float)CHUNK_VALUES_PER_SIDE).roundF().ToI());
			//Context.ChunkManager.Container.RemoveAround();
			//Context.ChunkManager.Container.InsertAround();
			Context.ChunkManager.Container.UpdateChunksContainer();
			sw.Stop();
			//AuxThread0Time.NewValue(sw.ElapsedTime());
		}
	}
	//Done = true;
}
