#pragma once

class AnimUnitls
{
public:
        //   Temoplate
        template <typename T> static T* FindFirstNotifyByClass(UAnimSequenceBase* Animation)
        {
                if (!Animation) { return nullptr; }

                const TArray<FAnimNotifyEvent> NotifyEvents = Animation->Notifies;

                for (auto NotifyEvent : NotifyEvents)
                {
                        T* const AnimNotify = Cast<T>(NotifyEvent.Notify);
                        if (AnimNotify)
                        {
                                return AnimNotify;
                        }
                }
                return nullptr;
        }
};
