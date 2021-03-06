; G-Code generated by Simplify3D(R) Version 4.0.0
; Dec 9, 2018 at 8:25:45 PM
; Settings Summary
;   processName,Process1
;   applyToModels,1mmSpacer
;   profileName,ABSX200 (modified)
;   profileVersion,2018-05-09 09:22:02
;   baseProfile,Default(2)(2)(2)(2)(2) (modified)
;   printMaterial,
;   printQuality,
;   printExtruders,
;   extruderName,Primary Extruder
;   extruderToolheadNumber,0
;   extruderDiameter,0.5
;   extruderAutoWidth,1
;   extruderWidth,0.6
;   extrusionMultiplier,1.03
;   extruderUseRetract,1
;   extruderRetractionDistance,1.5
;   extruderExtraRestartDistance,0
;   extruderRetractionZLift,0
;   extruderRetractionSpeed,900
;   extruderUseCoasting,1
;   extruderCoastingDistance,0.3
;   extruderUseWipe,0
;   extruderWipeDistance,5
;   primaryExtruder,0
;   layerHeight,0.25
;   topSolidLayers,4
;   bottomSolidLayers,3
;   perimeterOutlines,2
;   printPerimetersInsideOut,1
;   startPointOption,2
;   startPointOriginX,0
;   startPointOriginY,0
;   sequentialIslands,0
;   spiralVaseMode,0
;   firstLayerHeightPercentage,100
;   firstLayerWidthPercentage,105
;   firstLayerUnderspeed,0.5
;   useRaft,0
;   raftExtruder,0
;   raftTopLayers,3
;   raftBaseLayers,0
;   raftOffset,3
;   raftSeparationDistance,0.14
;   raftTopInfill,100
;   aboveRaftSpeedMultiplier,0.3
;   useSkirt,1
;   skirtExtruder,0
;   skirtLayers,1
;   skirtOutlines,3
;   skirtOffset,0
;   usePrimePillar,0
;   primePillarExtruder,999
;   primePillarWidth,12
;   primePillarLocation,7
;   primePillarSpeedMultiplier,1
;   useOozeShield,0
;   oozeShieldExtruder,999
;   oozeShieldOffset,2
;   oozeShieldOutlines,1
;   oozeShieldSidewallShape,1
;   oozeShieldSidewallAngle,30
;   oozeShieldSpeedMultiplier,1
;   infillExtruder,0
;   internalInfillPattern,Rectilinear
;   externalInfillPattern,Rectilinear
;   infillPercentage,100
;   outlineOverlapPercentage,15
;   infillExtrusionWidthPercentage,200
;   minInfillLength,2
;   infillLayerInterval,1
;   internalInfillAngles,45,-45
;   overlapInternalInfillAngles,0
;   externalInfillAngles,45,-45
;   generateSupport,1
;   supportExtruder,0
;   supportInfillPercentage,20
;   supportExtraInflation,1
;   supportBaseLayers,0
;   denseSupportExtruder,0
;   denseSupportLayers,0
;   denseSupportInfillPercentage,70
;   supportLayerInterval,1
;   supportHorizontalPartOffset,0.5
;   supportUpperSeparationLayers,1
;   supportLowerSeparationLayers,1
;   supportType,0
;   supportGridSpacing,1
;   maxOverhangAngle,45
;   supportAngles,90
;   temperatureName,Primary Extruder,Heated Bed
;   temperatureNumber,0,1
;   temperatureSetpointCount,1,1
;   temperatureSetpointLayers,1,1
;   temperatureSetpointTemperatures,230,100
;   temperatureStabilizeAtStartup,1,1
;   temperatureHeatedBed,0,1
;   temperatureRelayBetweenLayers,0,0
;   temperatureRelayBetweenLoops,0,0
;   fanLayers,1,2
;   fanSpeeds,0,40
;   blipFanToFullPower,1
;   adjustSpeedForCooling,1
;   minSpeedLayerTime,20
;   minCoolingSpeedSlowdown,60
;   increaseFanForCooling,1
;   minFanLayerTime,45
;   maxCoolingFanSpeed,80
;   increaseFanForBridging,1
;   bridgingFanSpeed,100
;   use5D,1
;   relativeEdistances,0
;   allowEaxisZeroing,1
;   independentExtruderAxes,0
;   includeM10123,0
;   stickySupport,1
;   applyToolheadOffsets,0
;   gcodeXoffset,0
;   gcodeYoffset,0
;   gcodeZoffset,0
;   overrideMachineDefinition,1
;   machineTypeOverride,0
;   strokeXoverride,298
;   strokeYoverride,275
;   strokeZoverride,250
;   originOffsetXoverride,0
;   originOffsetYoverride,0
;   originOffsetZoverride,0
;   homeXdirOverride,-1
;   homeYdirOverride,-1
;   homeZdirOverride,-1
;   flipXoverride,1
;   flipYoverride,-1
;   flipZoverride,1
;   toolheadOffsets,0,0|0,0|0,0|0,0|0,0|0,0
;   overrideFirmwareConfiguration,1
;   firmwareTypeOverride,RepRap (Marlin/Repetier/Sprinter)
;   GPXconfigOverride,r2
;   baudRateOverride,115200
;   overridePrinterModels,1
;   printerModelsOverride,LulzBot_TAZ3.stl
;   startingGcode,G28 ; home all axes
;   layerChangeGcode,
;   retractionGcode,
;   toolChangeGcode,
;   endingGcode,M400,M104 S0                        ; hotend off,M140 S0                        ; heated bed heater off (if you have it),M107                           ; fans off,G91                            ; relative positioning,G1 E-1 F300                    ; retract the filament a bit before lifting the nozzle, to release some of the pressure,G1 Z1 F3000   ; move Z up a bit and retract filament even more,G90                            ; absolute positioning,G1 X0 Y250                     ; move to cooling position,M84                            ; steppers off,G90                            ; absolute positioning,M117 TAZ Ready.,;{profile_string}
;   exportFileFormat,gcode
;   celebration,0
;   celebrationSong,Random Song
;   postProcessing,
;   defaultSpeed,2400
;   outlineUnderspeed,0.5
;   solidInfillUnderspeed,0.8
;   supportUnderspeed,0.8
;   rapidXYspeed,4800
;   rapidZspeed,1002
;   minBridgingArea,50
;   bridgingExtraInflation,0
;   bridgingExtrusionMultiplier,1
;   bridgingSpeedMultiplier,1
;   useFixedBridgingAngle,0
;   fixedBridgingAngle,0
;   applyBridgingToPerimeters,0
;   filamentDiameters,2.85|2.9|2.9|2.9|2.9|2.9
;   filamentPricesPerKg,13|13|13|13|13|13
;   filamentDensities,1.05|1.05|1.05|1.05|1.05|1.05
;   useMinPrintHeight,0
;   minPrintHeight,10
;   useMaxPrintHeight,0
;   maxPrintHeight,10
;   useDiaphragm,0
;   diaphragmLayerInterval,20
;   robustSlicing,1
;   mergeAllIntoSolid,0
;   onlyRetractWhenCrossingOutline,1
;   retractBetweenLayers,1
;   useRetractionMinTravel,0
;   retractionMinTravel,3
;   retractWhileWiping,0
;   onlyWipeOutlines,1
;   avoidCrossingOutline,0
;   maxMovementDetourFactor,3
;   toolChangeRetractionDistance,12
;   toolChangeExtraRestartDistance,-0.5
;   toolChangeRetractionSpeed,600
;   externalThinWallType,0
;   internalThinWallType,2
;   thinWallAllowedOverlapPercentage,10
;   singleExtrusionMinLength,1
;   singleExtrusionMinPrintingWidthPercentage,50
;   singleExtrusionMaxPrintingWidthPercentage,200
;   singleExtrusionEndpointExtension,0.2
;   horizontalSizeCompensation,0
G90
M82
M106 S255
G4 P500
M106 S0
M140 S100
M190 S100
M104 S230 T0
M109 S230 T0
G28 ; home all axes
G92 E0
G1 E-1.5000 F900
G1 Z0.250 F1002
; process Process1
; layer 1, Z = 0.250
T0
; tool H0.250 W0.630
; skirt
G1 X40.659 Y41.359 F4800
G1 E0.0000 F270
G92 E0
G1 X201.902 Y41.359 E4.1003 F1200
G1 X202.780 Y42.238 E4.1319
G1 X202.780 Y203.480 E8.2322
G1 X201.902 Y204.359 E8.2638
G1 X40.659 Y204.359 E12.3642
G1 X39.780 Y203.480 E12.3958
G1 X39.780 Y42.238 E16.4961
G1 X40.447 Y41.571 E16.5201
G1 X40.659 Y41.359 F1200
G1 X40.907 Y41.959 F4800
G92 E0
G1 X201.653 Y41.959 E4.0877 F1200
G1 X202.180 Y42.486 E4.1066
G1 X202.180 Y203.232 E8.1943
G1 X201.653 Y203.759 E8.2133
G1 X40.907 Y203.759 E12.3010
G1 X40.380 Y203.232 E12.3199
G1 X40.380 Y42.486 E16.4076
G1 X40.695 Y42.171 E16.4189
G1 X40.907 Y41.959 F1200
G1 X41.156 Y42.559 F4800
G92 E0
G1 X201.405 Y42.559 E4.0750 F1200
G1 X201.580 Y42.735 E4.0814
G1 X201.580 Y202.983 E8.1564
G1 X201.405 Y203.159 E8.1627
G1 X41.156 Y203.159 E12.2378
G1 X40.980 Y202.983 E12.2441
G1 X40.980 Y42.786 E16.3178
G1 X40.980 Y42.735 F1200
G1 X41.156 Y42.559 F1200
G92 E0
G1 E-1.5000 F900
; outer perimeter
G1 X41.595 Y43.174 F4800
G1 E0.0000 F900
G92 E0
G1 X200.965 Y43.174 E4.0527 F600
G1 X200.965 Y202.544 E8.1054
G1 X41.595 Y202.544 E12.1581
G1 X41.595 Y43.474 E16.2032
G1 X41.595 Y43.174 F600
G1 X41.965 Y43.544 F4800
G92 E0
G1 X41.965 Y202.174 E4.0339 F600
G1 X200.595 Y202.174 E8.0678
G1 X200.595 Y43.544 E12.1017
G1 X42.265 Y43.544 E16.1279
G1 X41.965 Y43.544 F600
G92 E0
G1 E-1.5000 F900
; layer 2, Z = 0.500
M106 S255
G4 P500
M106 S102
; tool H0.250 W0.600
G1 X41.580 Y43.159 F4800
G1 Z0.500 F1002
G1 E0.0000 F900
G92 E0
G1 X200.980 Y43.159 E3.8604 F1200
G1 X200.980 Y202.559 E7.7209
G1 X41.580 Y202.559 E11.5813
G1 X41.580 Y43.459 E15.4345
G1 X41.580 Y43.159 F1200
G1 X41.980 Y43.559 F4800
G92 E0
G1 X41.980 Y202.159 E3.8411 F1200
G1 X200.580 Y202.159 E7.6821
G1 X200.580 Y43.559 E11.5232
G1 X42.280 Y43.559 E15.3570
G1 X41.980 Y43.559 F1200
G92 E0
G1 E-1.5000 F900
; layer 3, Z = 0.750
G1 X41.580 Y43.159 F4800
G1 Z0.750 F1002
G1 E0.0000 F900
G92 E0
G1 X200.980 Y43.159 E3.8604 F1200
G1 X200.980 Y202.559 E7.7209
G1 X41.580 Y202.559 E11.5813
G1 X41.580 Y43.459 E15.4345
G1 X41.580 Y43.159 F1200
G1 X41.980 Y43.559 F4800
G92 E0
G1 X41.980 Y202.159 E3.8411 F1200
G1 X200.580 Y202.159 E7.6821
G1 X200.580 Y43.559 E11.5232
G1 X42.280 Y43.559 E15.3570
G1 X41.980 Y43.559 F1200
G92 E0
G1 E-1.5000 F900
; layer 4, Z = 1.000
G1 X41.580 Y43.159 F4800
G1 Z1.000 F1002
G1 E0.0000 F900
G92 E0
G1 X200.980 Y43.159 E3.8604 F1200
G1 X200.980 Y202.559 E7.7209
G1 X41.580 Y202.559 E11.5813
G1 X41.580 Y43.459 E15.4345
G1 X41.580 Y43.159 F1200
G1 X41.980 Y43.559 F4800
G92 E0
G1 X41.980 Y202.159 E3.8411 F1200
G1 X200.580 Y202.159 E7.6821
G1 X200.580 Y43.559 E11.5232
G1 X42.280 Y43.559 E15.3570
G1 X41.980 Y43.559 F1200
G92 E0
G1 E-1.5000 F900
; layer end
M400
M104 S0                        ; hotend off
M140 S0                        ; heated bed heater off (if you have it)
M107                           ; fans off
G91                            ; relative positioning
G1 E-1 F300                    ; retract the filament a bit before lifting the nozzle
 to release some of the pressure
G1 Z1 F3000   ; move Z up a bit and retract filament even more
G90                            ; absolute positioning
G1 X0 Y250                     ; move to cooling position
M84                            ; steppers off
G90                            ; absolute positioning
M117 TAZ Ready.
;{profile_string}
; Build Summary
;   Build time: 0 hours 6 minutes
;   Filament length: 174.0 mm (0.17 m)
;   Plastic volume: 1109.78 mm^3 (1.11 cc)
;   Plastic weight: 1.17 g (0.00 lb)
;   Material cost: 0.02
