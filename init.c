/***********************************************************************************************
 ***                The Ultimate Survival in Pripyat - Server Script                         ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : DayZ S.T.A.L.K.E.R                                           *
 *                                                                                             *
 *                    File Name : INIT.C                                                       *
 *                                                                                             *
 *                   Programmer : Victor Guerra-Espinoza                                       *
 *                                                                                             *
 *                   Start Date : June 4, 2023                                                 *
 *                                                                                             *
 *                  Last Update : June 4, 2023                                                 *
 *                                                                                             *
 *--------------------------------------------------------------------------------------------*/

 /*
  *  DayZ Standalone Modding
  *  Mission Server Class
  *  Custom Mission Script
  *
  *  Last Update: June 4, 2023
  *  Author: Victor Espinoza
  */


void main()
{
    //INIT ECONOMY--------------------------------------
    Hive ce = CreateHive();
    if (ce)
        ce.InitOffline();

    //EXPORTING FOR PRIPYAT -UNCOMMENT TO EXPORT NEW FILES
        //GetCEApi().ExportProxyData("0 0 0", 100000);
        //GetCEApi().ExportClusterData();

    //DATE RESET AFTER ECONOMY INIT-------------------------
    int year, month, day, hour, minute;
    int reset_month = 1, reset_day = 1;
    GetGame().GetWorld().GetDate(year, month, day, hour, minute);

    if ((month == reset_month) && (day < reset_day))
    {
        GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
    }
    else
    {
        if ((month == reset_month + 1) && (day > reset_day))
        {
            GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
        }
        else
        {
            if ((month < reset_month) || (month > reset_month + 1))
            {
                GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
            }
        }
    }
}

/*
 *  This is the CustomMission class. It extends the MissionServer class
 *  and overrides some of its functions to provide custom functionality.
 */
class CustomMission : MissionServer
{
    /*
     *  This function is called when a new player character is created.
     *  It returns a PlayerBase instance representing the new character.
     */
    override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
    {
        Entity player_ent = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
        m_player = cast<PlayerBase>(player_ent);
        GetGame().SelectPlayer(identity, m_player);

        return m_player;
    }

    /*
     *  This function is called to add magazines to a player's inventory.
     *  The type of magazine and the count are specified as parameters.
     */
    void AddMags(PlayerBase player, string mag_type, int count)
    {
        if (count < 1)
            return;

        EntityAI mag;

        for (int i = 0; i < count; i++) {
            mag = player.GetInventory().CreateInInventory(mag_type);
        }

        player.SetQuickBarEntityShortcut(mag, 1, true);
    }

    /*
     *  This function is called when a player character is spawned.
     *  It handles initialization of the character and spawning of items.
     */
    override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
    {
        EntityAI item;
        player.RemoveAllItems();

        item = player.GetInventory().CreateInInventory("CivilianBelt"); SetRandomHealth(item);
        player.GetInventory().CreateInInventory("Canvas_Backpack_Blue");
        player.GetInventory().CreateInInventory("KMP_SlackPants_Shitty");
        item = player.GetInventory().CreateInInventory("Wool_GreatCoat_Olive"); SetRandomHealth(item);
        player.GetInventory().CreateInInventory("DressShoes_Brown");
        player.GetInventory().CreateInInventory("mm_neck_gaiter_green");
        player.GetInventory().CreateInInventory("RadarCap_Brown");
        player.GetInventory().CreateInInventory("DONDRINK_BEER_GREEN");
        player.GetInventory().CreateInInventory("Fingerless_Gloves_Brown");
        player.GetInventory().CreateInInventory("UA_kvas_paras");
        player.GetInventory().CreateInInventory("DONFOOD_BREAD2");
        player.GetInventory().CreateInInventory("UA_Food_ban_fushonka2");
        player.GetInventory().CreateInInventory("UA_Food_ban_fushonka1_Opened");
        player.GetInventory().CreateInInventory("KMP_BuckKnife");
        player.GetInventory().CreateInInventory("KMP_Radio_UV5R");
        player.GetInventory().CreateInInventory("EFT_Food_Alyonka");
        player.GetInventory().CreateInInventory("AMS_Bandage");
        player.GetInventory().CreateInInventory("Flashlight");
        player.GetInventory().CreateInInventory("Rfa_Varta_C");

        EntityAI itemTop;
        EntityAI itemEnt;
        ItemBase itemBs;
        float rand;

        itemTop = player.FindAttachmentBySlotName("Body");

        if (itemTop)
        {
            itemEnt = itemTop.GetInventory().CreateInInventory("Rag");
            if (Class.CastTo(itemBs, itemEnt))
                itemBs.SetQuantity(4);

            SetRandomHealth(itemEnt);

            itemEnt = itemTop.GetInventory().CreateInInventory("RoadFlare");
            SetRandomHealth(itemEnt);

            itemEnt = itemTop.GetInventory().CreateInInventory("StoneKnife");
            SetRandomHealth(itemEnt);
        }

        AddMags(player, "Mag_IZH18_20Rnd", 3);
    }

    /*
     *  This function is used to set a random health value for items.
     *  The health value is between 0.25 and 1.
     */
    void SetRandomHealth(EntityAI item)
    {
        float rand = Math.RandomFloatInclusive(0.25, 1.0);
        item.SetHealth("", "", rand);
    }
};

Mission CreateCustomMission(string path)
{
    return new CustomMission();
}
