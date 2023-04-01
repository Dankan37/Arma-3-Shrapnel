//Debug fnction to test performance
_pos = param [0];
_shell = param[1, "Sh_SHRP_82mm_AMOS"];
_shellParams = param[2, []];

_shell = _shell createVehicle _pos;

if(count _shellParams == 0) then {
	_shellParams = getArray (configOf _shell >> "SHRP_shellParam");
};

_outArr = [_shell] + _shellParams;
_outArr call SHRP37_fnc_createShrapnel;