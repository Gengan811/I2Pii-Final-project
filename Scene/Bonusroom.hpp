#include <list>
#include <memory>
#include <utility>
#include <vector>

#include "Engine/IScene.hpp"
#include "Engine/Point.hpp"
#include "Player/Player.hpp"
class PlayScene;
class Bonusroom final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
public:
    explicit Bonusroom() = default;
    void Initialize() override;
    void Terminate() override;
    void ButtonOnClick(int x);
};
#endif //BONUSROOM_H