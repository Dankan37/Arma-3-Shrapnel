//Initializes a shell for the SHRAPNEL mod
//Will trigger when a certain shell is fired and will launch the shrpanel function when the conditions are met

_shell = param [0, objNull, [objNull]];

if(isNull _shell) exitWith {};

_shell spawn {
	_shell = _this;
	//Parameters for the shell
	_shellParams = getArray (configOf _shell >> "SHRP_shellParam");

	//when it's mean to explode
	_burstHeight = getNumber (configOf _shell >> "SHRP_burstHeight");
	if((_shellParams # 7) == 1) then {
		sleep 0.5;
		if(!alive _shell) exitWith {};
	} else {
		_burstHeight = _burstHeight + random 5; 
	};

	//Wait until it's falling
	waitUntil {(velocity _shell select 2) < 0};

	//Wait to explode
	waitUntil {
		((getPosATL _shell) select 2) < _burstHeight;
	};

	//Launch the Shrapnel script with all the params
	_outArr = [_shell] + _shellParams;
	_outArr call SHRP37_fnc_createShrapnel;
};

true;

