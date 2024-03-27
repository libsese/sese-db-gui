/**
 * Should match main/preload.ts for typescript support in renderer
 */
export default interface ElectronApi {
  open_url: (url: string) => void
  open_db: (host: string, port: Number, db: string, user: string, pwd: string) => void
  get_tables: (db_name: string) => Promise<string[]>,
  get_table_headers: (db_name: string, tb_name: string) => Promise<string[]>,
  get_table_contents: (tb_header: string[], tb_name: string) => Promise<string[]>,
}

declare global {
  interface Window {
    electronAPI: ElectronApi,
  }
}
