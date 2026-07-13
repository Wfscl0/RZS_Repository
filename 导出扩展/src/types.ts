export interface ExtensionSettings {
  outputDirectory: string;
  askEveryTime: boolean;
  createProjectSubdirectory: boolean;
}

export interface ExportUnit {
  schematic: IDMT_SchematicItem;
  page: IDMT_SchematicPageItem;
  fileStem: string;
}

export interface NetlistSelection {
  enumKey: 'JLCEDA_PRO' | 'EASYEDA_PRO';
  value: ESYS_NetlistType;
}

export type SavedFileMode = 'direct' | 'fallback';

export interface SavedFileRecord {
  kind: 'BOM' | 'Netlist' | 'Log';
  fileName: string;
  size: number;
  mode: SavedFileMode;
  verified: boolean;
  path?: string;
}

export interface ComponentSnapshot {
  schematicUuid: string;
  schematicName: string;
  pageName: string;
  primitiveId: string;
  designator: string;
  subPartName?: string;
  hasFootprint: boolean;
}
