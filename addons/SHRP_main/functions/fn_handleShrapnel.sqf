//Function that is called when an EH regarding a shrapnel shell is triggered
//Avoids having to check for magazine as long as SHRP_burstHeight is defined
params ["_unit", "_weapon", "_muzzle", "_mode", "_ammo", "_magazine", "_projectile", "_gunner"];

if((getNumber (configOf _projectile >> 'SHRP_burstHeight')) == 0) exitWith {};
[_projectile] call SHRP37_fnc_initializeShell;

true;