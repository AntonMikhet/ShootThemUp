#pragma once

class STUUtils
{
public:
        template <typename T> static T* GetSTUPlayerComponent(APawn* PlayerPawb)
        {
                if (!PlayerPawb) { return nullptr; }

                T* Component = Cast<T>(PlayerPawb->GetComponentByClass(T::StaticClass()));
                if (!Component) { return nullptr; }
                return Component;
        }
};
