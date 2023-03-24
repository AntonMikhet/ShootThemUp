// Shoot Them Up Game. All Rights Recieved.


#include "AnimNotify/STUAnimNotify.h"

void USTUAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
        Super::Notify(MeshComp, Animation);

        OnNotified.Broadcast(MeshComp);
}
