#pragma once
#include  <assert.h>
#include "playScene.h"
#include "CharaValue.h"
#include "RoundShadowManager.h"
#include <vector>

class RoundShadow
{
public:
    RoundShadow(const float& _size)
    {
        SceneBase* scene = SceneManager::CurrentScene();
        PlayScene* pScene = dynamic_cast<PlayScene*>(scene);
        texture = pScene->GetShadowTexture();
        assert(texture > 0);
        alphaRate = CHARA_SHADOW_DEF_ALPHA_RATE;
        size = _size;
        doAppear = true;
        pos = VZero;
        norm = VGet(0, 1, 0);
    }
    ~RoundShadow() {}
    void Draw()
    {
        if (!doAppear)
            return;
        DrawTexturedQuadShadow(pos, size, texture, alphaRate);
    }

    void SetPos(const VECTOR& _pos) { pos = _pos; }
    void SetNorm(const VECTOR& _norm) { norm = _norm; }
    void SetAlpha(const float& _alphaRate) { alphaRate = _alphaRate; }
    void SetDoAppear(const bool& _appaer) { doAppear = _appaer; }

private:
    void DrawTexturedQuadShadow(
        const VECTOR& center,
        float size,
        int textureHandle,
        float alpha
    )
    {
        // アルファブレンド・Zバッファ設定（必要に応じて）
        SetWriteZBufferFlag(FALSE);
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(alpha * 255));

        float half = size / 2.0f;

        VERTEX3D verts[4];

        // 左下
        verts[0].pos = VGet(center.x - half, center.y, center.z - half);
        verts[0].u = 0.0f; verts[0].v = 1.0f;

        // 左上
        verts[1].pos = VGet(center.x - half, center.y, center.z + half);
        verts[1].u = 0.0f; verts[1].v = 0.0f;

        // 右上
        verts[2].pos = VGet(center.x + half, center.y, center.z + half);
        verts[2].u = 1.0f; verts[2].v = 0.0f;       
                                                    
        // 右下                                     
        verts[3].pos = VGet(center.x + half, center.y, center.z - half);
        verts[3].u = 1.0f; verts[3].v = 1.0f;

        for (int i = 0; i < 4; ++i)
        {
            verts[i].dif = GetColorU8(255, 255, 255, 255);
            verts[i].norm = norm;
        }

        // 三角形2枚で四角形を構成（0-1-2, 0-2-3）
        unsigned short indices[] = { 0, 1, 2, 0, 2, 3 };

        DrawPolygonIndexed3D(verts, 4, indices, 6, textureHandle, TRUE);

        // 状態を戻す
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        SetWriteZBufferFlag(TRUE);
    }

    int texture;
    VECTOR pos;
    VECTOR norm;
    float size;
    float alphaRate;
    bool doAppear;
};