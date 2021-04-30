#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"

#include <memory>

#include "CGameStateRun.h"

#include <algorithm>

namespace game_framework
{
	void CGameStateRun::ItemInteract(shared_ptr<Item> item, shared_ptr<Player> player,PlayerCoordinate coordinate, int direction)
	{
		//获取玩家坐标
		const int x1 = coordinate.x1;
		const int y1 = coordinate.y1;
		const int x2 = coordinate.x2;
		const int y2 = coordinate.y2;

		//获取物品类型
		int type = item->GetType();

		if (type == 200 && player->is_boy)//fire diamond
		{
			CAudio::Instance()->Play(AUDIO_DIAMOND, true);
			player->score++;
			item->is_visibale = false;
			//DeleteItem(item);
			CAudio::Instance()->Play(AUDIO_DIAMOND, false);

			TRACE("boy score=%d, total=%d\n", player->score, score_boy);
		}
		else if (type == 201 && !player->is_boy)//water diamond
		{
			CAudio::Instance()->Play(AUDIO_DIAMOND, true);
			player->score++;
			item->is_visibale = false;
			//DeleteItem(item);
			CAudio::Instance()->Play(AUDIO_DIAMOND, false);
			TRACE("girl score=%d, total=%d\n", player->score, score_boy);
		}
		//todo fix: 当水池正下方一格有钻石时，玩家会顶穿水池下方
		else if (type == 300 || type == 301 || type == 302)//ֻ只有水池中部有效
		{
			if (direction == DIRECTION_DOWN)//ֻ如果玩家下方接触水池上方
			{
				CAudio::Instance()->Play(AUDIO_LAKE, true);
				CAudio::Instance()->Play(AUDIO_LAKE, false);
				if (type == 300 && !player->is_boy)//fire & girl
				{
					//CAudio::Instance()->Play(AUDIO_DIE, true);
					PlayerDie(player);
					//CAudio::Instance()->Stop(AUDIO_DIE);
				}
				else if (type == 301 && player->is_boy)//water & boy
				{
					//CAudio::Instance()->Play(AUDIO_DIE, true);
					PlayerDie(player);
					//CAudio::Instance()->Stop(AUDIO_DIE);
				}
				else if (type == 302)//toxic && both
				{
					//CAudio::Instance()->Play(AUDIO_DIE, true);
					PlayerDie(player);
					//CAudio::Instance()->Stop(AUDIO_DIE);
				}
				
			}
		}
		else if (type == 500)//按钮
		{
			//指针转到switch类
			shared_ptr<Switch> switch_ptr = std::static_pointer_cast<Switch>(item);

			if ((x1 > switch_ptr->GetX1() - 16) && (x2 < switch_ptr->GetX2() + 16) /*&& (y2 > this->GetY1())*/)//扩大判定范围？
			{
				if (switch_ptr->status == SWITCH_RELEASE)//按钮只能被按下一次
				{
					switch_ptr->is_on = true;
					switch_ptr->status = SWITCH_PRESS;
				}
			}
			else
			{
				if (switch_ptr->status == SWITCH_PRESS)//玩家离开后按钮被松开
				{
					switch_ptr->is_on = false;
					switch_ptr->status = SWITCH_RELEASE;
				}
			}
			//触发开关
			switch_ptr->Trigger();
		}
		else if (type == 501)//拉杆
		{
			//指针转到switch类
			shared_ptr<Switch> switch_ptr = std::static_pointer_cast<Switch>(item);

			if ((x1 > switch_ptr->GetX1() - 16) && (x2 < switch_ptr->GetX2() + 16) /*&& (y2 > this->GetY1())*/)//扩大判定范围？
			{
				if (switch_ptr->status == SWITCH_RELEASE)//拉杆被触发，转换状态
				{
					switch_ptr->is_on = !switch_ptr->is_on;
					switch_ptr->status = SWITCH_PRESS;
				}
			}
			else
			{
				if (switch_ptr->status == SWITCH_PRESS)//玩家离开后，不松开
				{
					switch_ptr->status = SWITCH_RELEASE;
				}
			}
			//触发开关
			switch_ptr->Trigger();
		}
		else if (type == 400 && player->is_boy)
		{
			//指针转到door类
			shared_ptr<Door> door_ptr = std::static_pointer_cast<Door>(item);

			if ((x1 > door_ptr->GetX1()) && (x2 < door_ptr->GetX2()))//玩家完全进入门内
			{
				if (door_ptr->status == DOOR_LEAVE)
				{
					door_ptr->status = DOOR_ENTER;
					
					PlayerReachExit(player, true);
					door_ptr->AnimationOpenDoor();//触发开门动画
					CAudio::Instance()->Play(AUDIO_DOOR, true);
					CAudio::Instance()->Play(AUDIO_DOOR, false);

				}
			}
			else//玩家离开门
			{
				if (door_ptr->status == DOOR_ENTER)
				{
					door_ptr->status = DOOR_LEAVE;

					PlayerReachExit(player, false);
					door_ptr->AnimationCloseDoor();//触发关门动画
					CAudio::Instance()->Play(AUDIO_DOOR, true);
					CAudio::Instance()->Play(AUDIO_DOOR, false);
				}
			}
		}
		else if (type == 401 && !player->is_boy)
		{
			//指针转到door类
			shared_ptr<Door> door_ptr = std::static_pointer_cast<Door>(item);

			if ((x1 > door_ptr->GetX1()) && (x2 < door_ptr->GetX2()))//玩家完全进入门内
			{
				if (door_ptr->status == DOOR_LEAVE)
				{
					door_ptr->status = DOOR_ENTER;

					PlayerReachExit(player, true);
					door_ptr->AnimationOpenDoor();//触发开门动画
					CAudio::Instance()->Play(AUDIO_DOOR, true);
					CAudio::Instance()->Play(AUDIO_DOOR, false);
				}
			}
			else//玩家离开门
			{
				if (door_ptr->status == DOOR_ENTER)
				{
					door_ptr->status = DOOR_LEAVE;

					PlayerReachExit(player, false);
					door_ptr->AnimationCloseDoor();//触发关门动画
					CAudio::Instance()->Play(AUDIO_DOOR, true);
					CAudio::Instance()->Play(AUDIO_DOOR, false);
				}
			}
		}
		else
		{
		
		}
	}
}