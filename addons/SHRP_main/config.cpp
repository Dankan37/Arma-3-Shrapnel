#include "BIS_AddonInfo.hpp"
class CfgPatches {
    class SHRP_main {
        requiredAddons[] = {"A3_Static_F_Mortar_01", "A3_Armor_F_Gamma_MBT_01", "A3_Armor_F_Gamma_MBT_02"};
        requiredVersion = 0.1;
        units[] = {};
        weapons[] = {};
    };
};

class CfgFunctions
{
	class SHRP37
	{
		class functions
		{
			file = "SHRP_main\functions";
			
            class initializeShell {};
            class createShrapnel {};
            class ShrapnelAtPos {};
            class handleShrapnel {};
		};
	};
};

//["ShellBase","ShellCore","Default"]
class cfgAmmo {
	class Sh_82mm_AMOS;
	class Sh_SHRP_82mm_AMOS: Sh_82mm_AMOS {
		indirectHit = 0;
		explosionEffects = "";
		craterEffects = "";
		explosionType = "";

        SHRP_burstHeight = 20;
        SHRP_shellParam[] = {45, 7, 4, 1800, "B_408_Ball", 5, "APERSMine",0};
	};

    class Sh_155mm_AMOS;
    class Sh_SHRP_155mm_AMOS: Sh_155mm_AMOS {
		indirectHit = 0;
		explosionEffects = "";
		craterEffects = "";
		explosionType = "";

        SHRP_burstHeight = 25;
        SHRP_shellParam[] = {70, 12, 5, 2200, "B_127x108_Ball", 5, "APERSMine",0};
	};

    class R_230mm_fly;
    class R_230mm_SHRP: R_230mm_fly {
        indirectHit = 0;
		explosionEffects = "";
		craterEffects = "";
		explosionType = "";

        SHRP_burstHeight = 55;
        SHRP_shellParam[] = {190, 12, 5, 2500, "B_30mm_APFSDS", 3, "DemoCharge_F",0};
    };

    class G_40mm_HE;
    class G_40mm_SHRP: G_40mm_HE {
        explosive = 0;
        hit = 0;
        indirectHit = 0;
        timeToLive = 35;
        warheadName = "SHRP";

        SHRP_burstHeight = 1.5;
        SHRP_shellParam[] = {25, 4, 4, 1750, "B_408_Ball", 4, "APERSMine", 1};
    };
};

class cfgMagazines {
    class CA_Magazine;
    class VehicleMagazine: CA_Magazine {};
    class 32Rnd_155mm_Mo_shells: VehicleMagazine {};
    class 8Rnd_82mm_Mo_shells: VehicleMagazine {};

    class 6Rnd_82mm_Mo_SHRP_shells: 8Rnd_82mm_Mo_shells {
        ammo = "Sh_SHRP_82mm_AMOS";
        count = 6;
        displayName = "Airburst Mortar Shells";
        displayNameShort = "Shrapnel";
    };

    class 12Rnd_155mm_Mo_SHRP_shells: 32Rnd_155mm_Mo_shells {
        ammo = "Sh_SHRP_155mm_AMOS";
        count = 12;
        displayName = "Airburst Shells";
        displayNameShort = "Shrapnel";
    };

    class 12Rnd_230mm_rockets;
    class 12Rnd_230mm_rockets_SHRP: 12Rnd_230mm_rockets {
        ammo = "R_230mm_SHRP";
    };

    class 1Rnd_HE_Grenade_shell;
    class 1Rnd_SHRP_Grenade_shell: 1Rnd_HE_Grenade_shell {
        author = "Dankan37";
        ammo = "G_40mm_SHRP";
        displayName = "40 mm Airburst Grenade Round";
        displayNameShort = "Airburst Grenade";
    };
};

class cfgWeapons {
    class CannonCore;
    class mortar_155mm_AMOS: CannonCore {
        magazines[] += {"12Rnd_155mm_Mo_SHRP_shells"};
    };
    class mortar_82mm: CannonCore {
        magazines[] += {"6Rnd_82mm_Mo_SHRP_shells"};
    };
    class rockets_230mm_GAT: CannonCore 
	{
        scope = 2;
		scopeCurator = 2;
		magazines[] += {"12Rnd_230mm_rockets_SHRP"};
	};

    class GrenadeLauncher;
    class UGL_F: GrenadeLauncher {
		magazines[] += {"1Rnd_SHRP_Grenade_shell"};
		class EventHandlers
		{
            class SHRP {
				fired = "_this call SHRP37_fnc_handleShrapnel";
			};
		};
	};

    //I literally got no clue of what I'm doing :^)
    class Rifle;
    class Rifle_Base_F;
    class arifle_MX_Base_F: Rifle_Base_F {
        class GL_3GL_F;
    };
    class arifle_MX_GL_F : arifle_MX_Base_F {
        class GL_3GL_F: GL_3GL_F {
            magazines[] += {"1Rnd_SHRP_Grenade_shell"};

            class EventHandlers
            {
                class SHRP {
				    fired = "_this call SHRP37_fnc_handleShrapnel";
			    };
            };
        };        
    };
};

class cfgVehicles {
    class LandVehicle;
    class StaticWeapon: LandVehicle {
        class Turrets;
    };
    class StaticMortar: StaticWeapon {
        class Turrets: Turrets {
            class MainTurret;
        };
        class EventHandlers;
    };
    class Mortar_01_base_F: StaticMortar {
        class Turrets: Turrets {
            class MainTurret: MainTurret {
                magazines[] += {"6Rnd_82mm_Mo_SHRP_shells"};
            };
        };

        class EventHandlers: EventHandlers {
			class SHRP {
				fired = "_this call SHRP37_fnc_handleShrapnel";
			};
		};
    };

    class Tank_F: LandVehicle {};
    class MBT_01_base_F: Tank_F {
        class Turrets {
            class MainTurret;
        };
        class EventHandlers;
    };
    class MBT_01_arty_base_F : MBT_01_base_F {
        class Turrets: Turrets { 
            class MainTurret: MainTurret {
                magazines[] += {"12Rnd_155mm_Mo_SHRP_shells"};
            };
        };

        class EventHandlers: EventHandlers {
			class SHRP {
			    fired = "_this call SHRP37_fnc_handleShrapnel";
			};
		};
    };

    class MBT_02_base_F: Tank_F {
        class Turrets {
            class MainTurret;
        };
        class EventHandlers;
    };
    class MBT_02_arty_base_F : MBT_02_base_F {
        class Turrets: Turrets { 
            class MainTurret: MainTurret {
                magazines[] += {"12Rnd_155mm_Mo_SHRP_shells"};
            };
        };

        class EventHandlers: EventHandlers {
			class SHRP {
			    fired = "_this call SHRP37_fnc_handleShrapnel";
			};
		};
    };

    class MBT_01_mlrs_base_F: MBT_01_base_F {};
    class B_MBT_01_mlrs_base_F: MBT_01_mlrs_base_F {};
    class B_MBT_01_mlrs_F: B_MBT_01_mlrs_base_F {};

    class SHRP_B_MBT_01_mlrs_F: B_MBT_01_mlrs_F {
        displayName = "M5 Sandstorm MLRS (Shrapnel)";

        class Turrets: Turrets { 
            class MainTurret: MainTurret {
                magazines[] = {"12Rnd_230mm_rockets_SHRP"};
            };
        };

        class EventHandlers
		{
			class SHRP {
			    fired = "_this call SHRP37_fnc_handleShrapnel";
			};
		};
    };
};
