//Creates shrpanel for an object
_shell 		= param[0, objNull, [objNull]];
_radius 	= param[1, 30];
_frags 		= param[2, 6];
_levels 	= param[3, 4];
_velocity 	= param[4, 1400];
_type 		= param[5, "B_408_Ball"];
_deviation 	= param[6, 5];
_explosive 	= param[7, "APERSMine"];


//Start
_pos = position _shell;
deleteVehicle _shell;

//Mine explosion 
_exp = createMine [_explosive, _pos, [], 0];
//_exp setPosASL _pos;
_exp setDamage 1;

_entities = _pos nearEntities _radius;
_maxDeviation = _velocity * sin(_deviation);
_maxDeviationHalf = _maxDeviation/2;

{
	if(!alive _x) then {continue};
	_posTgt = position _x;
	_relVersor = vectorNormalized (_pos vectorFromTo _posTgt);
	for "_i" from 0 to _frags do {
		_ammo = _type createVehicle _pos;
		_v =  _relVersor vectorMultiply _velocity;
		_v = _v vectorAdd ([random 1,random 1, 0.5 + random 1] vectorMultiply (random [-_maxDeviation, 0 , _maxDeviation]));
		_ammo setVelocity _v;
		//[str _ammo, "onEachFrame", { drawLine3D [_this # 0, _this # 1, [1,1,1,1]]}, [_pos, _pos vectorAdd _v]] call BIS_fnc_addStackedEventHandler;
	};
}forEach _entities;

_verticalAngle = 90 / _levels;
_N = (_frags * 2) max 20;
for "_i" from 1 to _N do {
	_startAngle = random 360;
	_t = 360/_N;
	_angle = _t * _i + _startAngle;
	_tSin = sin(_angle);
	_tCos = cos(_angle);
	
	for "_j" from 1 to _levels do {
		_verticalSpeed = -_velocity * sin(_verticalAngle * _j);
		_pickedRandom = random [-_maxDeviation, -_maxDeviationHalf , _maxDeviationHalf];
		_tempVal = _pickedRandom + _velocity;
		_ammo = _type createVehicle _pos;
		_vx = _tempVal * _tCos;
		_vy = _tempVal * _tSin;
		_vz = _verticalSpeed + _pickedRandom;
		_v = [_vx, _vy, _vz];
		_ammo setVelocity _v;

		//[str _ammo, "onEachFrame", { drawLine3D [_this # 0, _this # 1, [1,1,1,1]]}, [_pos, _pos vectorAdd _v]] call BIS_fnc_addStackedEventHandler;
	}
};
