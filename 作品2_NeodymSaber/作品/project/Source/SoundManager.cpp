#include "SoundManager.h"
#include <assert.h>
#include "SoundValue.h"

SoundManager::SoundManager(SceneBase* _scene) :GameObject(_scene)
{
	Load("PlayBgm", "data/sound/playBgm.mp3", SOUND_VOLUME_PLAY_BGM);
	Load("GameOverBgm", "data/sound/gameOverBgm.wav", SOUND_VOLUME_GAME_OVER_BGM);
	Load("ResultBgm", "data/sound/resultBgm.wav", SOUND_VOLUME_RESULT_BGM);
	Load("TitleBgm", "data/sound/titleBgm.wav", SOUND_VOLUME_TITLE_BGM);
	Load("Push", "data/sound/push.mp3", SOUND_VOLUME_PUSH);
	Load("Cursor", "data/sound/cursor.mp3", SOUND_VOLUME_CURSOR);
	Load("Start", "data/sound/start.mp3", SOUND_VOLUME_START);
	Load("Clear", "data/sound/clear.mp3", SOUND_VOLUME_CLEAR);

	Load("SnapAttract", "data/sound/snap_attract.mp3", SOUND_VOLUME_SNAP_ATTRACT);
	Load("SnapUnion1", "data/sound/snap_union.wav", SOUND_VOLUME_SNAP_UNION_1);
	Load("SnapUnion2", "data/sound/snap_union2.wav", SOUND_VOLUME_SNAP_UNION_2);

	Load("PlayerAttackSwing_Small", "data/sound/swordAttackSwing_small.mp3", SOUND_VOLUME_PLAYER_ATTACK_SWING_SMALL);
	Load("PlayerAttackSwing_Medium", "data/sound/swordAttackSwing_medium.mp3", SOUND_VOLUME_PLAYER_ATTACK_SWING_MEDIUM);
	Load("PlayerAttackSwing_Large", "data/sound/swordAttackSwing_large.mp3", SOUND_VOLUME_PLAYER_ATTACK_SWING_LARGE);

	int size = (int)(sizeof(PLAYER_ATTACK_SOUND_PITCH) / sizeof(PLAYER_ATTACK_SOUND_PITCH[0]));
	for (int p = 0; p < size; p++)
	{
		SetCreateSoundPitchRate(PLAYER_ATTACK_SOUND_PITCH[p]);
		std::string num = std::to_string(p);
		Load("PlayerAttackHit_Small" + num, "data/sound/swordAttackHit_small.mp3", SOUND_VOLUME_PLAYER_ATTACK_HIT_SMALL);
		Load("PlayerAttackHit_Medium" + num, "data/sound/swordAttackHit_medium.wav", SOUND_VOLUME_PLAYER_ATTACK_HIT_MEDIUM);
		Load("PlayerAttackHit_Large" + num, "data/sound/swordAttackHit_large.mp3", SOUND_VOLUME_PLAYER_ATTACK_HIT_LARGE);
		SetCreateSoundPitchRate(0);
	}

	Load("PlayerAttractAttackHit", "data/sound/attractAttackHit.mp3", SOUND_VOLUME_PLAYER_ATTRACT_ATTACK_HIT);
			  
	Load("SwordPierce", "data/sound/swordPierce.mp3", SOUND_VOLUME_SWORD_PIERCE);
	Load("PlayerDamage", "data/sound/playerDamage.mp3", SOUND_VOLUME_PLAYER_DAMAGE);
	Load("EnemyAttackWarning", "data/sound/enemyAttackWarning.mp3", SOUND_VOLUME_ENEMY_ATTACK_WARNING);
	Load("ThrowSword", "data/sound/throwSword.mp3", SOUND_VOLUME_THROW_SWORD);
	
	Load("PlayerAvoid1", "data/sound/playerAvoid1.mp3", SOUND_VOLUME_PLAYER_AVOID[0]);
	Load("PlayerAvoid2", "data/sound/playerAvoid2.mp3", SOUND_VOLUME_PLAYER_AVOID[1]);

	Load("EnemyDie", "data/sound/enemyDie.wav", SOUND_VOLUME_ENEMY_DIE);
	Load("EnemyAttack_CloseRange", "data/sound/enemyAttack_closeRange.mp3", SOUND_VOLUME_ENEMY_ATTACK_CLOSE_RANGE);
	Load("EnemyAttack_LongRange", "data/sound/enemyAttack_longRange.wav", SOUND_VOLUME_ENEMY_ATTACK_LONG_RANGE);

	Load("Heal", "data/sound/heal.mp3", SOUND_VOLUME_HEAL);

	Load("PlayerVoice_Attack_Small", "data/sound/playerVoice_attack_small.wav", SOUND_VOLUME_PLAYER_VOICE_ATTACK_SMALL);
	Load("PlayerVoice_Attack_Medium", "data/sound/playerVoice_attack_medium.wav", SOUND_VOLUME_PLAYER_VOICE_ATTACK_MEDIUM);
	Load("PlayerVoice_Attack_Large", "data/sound/playerVoice_attack_large.wav", SOUND_VOLUME_PLAYER_VOICE_ATTACK_LARGE);
	Load("PlayerVoice_Damage_Small", "data/sound/playerVoice_damage_small.wav", SOUND_VOLUME_PLAYER_VOICE_DAMAGE_SMALL);
	Load("PlayerVoice_Damgae_Medium", "data/sound/playerVoice_damage_medium.wav", SOUND_VOLUME_PLAYER_VOICE_DAMAGE_MEDIUM);

	Load("PlayerVoice_Avoid", "data/sound/playerVoice_avoid.wav", SOUND_VOLUME_PLAYER_VOICE_AVOID);
	Load("PlayerVoice_AttractAttack", "data/sound/playerVoice_attractAttack.wav", SOUND_VOLUME_PLAYER_VOICE_ATTRACT_ATTACK);

	Load("PlayerVoice_GameOver", "data/sound/playerVoice_gameOver.wav", SOUND_VOLUME_PLAYER_VOICE_GAME_OVER);
	Load("PlayerVoice_Clear", "data/sound/playerVoice_clear.wav", SOUND_VOLUME_PLAYER_VOICE_CLEAR);

	for (auto& s : hSounds)
		assert(s.second > 0);
}

SoundManager::~SoundManager()
{
	for (auto& s : hSounds)
		DeleteSoundMem(s.second);
	hSounds.clear();
}

void SoundManager::Update()
{
	for (auto& p : playSounds)
		p.second = 0;
}

void SoundManager::Play(const std::string& _name, const bool& _loop)
{
	if (playSounds.count(_name) == 0)
		playSounds.insert({ _name, 0 });
	else
	{
		playSounds[_name]++;
		if (playSounds[_name] > SOUND_SAME_TIME_MAX)
			return;
	}
	PlaySoundMem(hSounds[_name], _loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK);
}

void SoundManager::Stop(const std::string& _name)
{
	StopSoundMem(hSounds[_name]);
}

void SoundManager::Load(const std::string& _name, const std::string& _fileName, const float& _volume)
{
	hSounds.insert({ _name, LoadSoundMem(_fileName.c_str()) });
	ChangeVolumeSoundMem((int)((_volume / 100) * 255), hSounds[_name]);
}
