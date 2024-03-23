/**
 * Should match main/preload.ts for typescript support in renderer
 */
export default interface ElectronApi {
  open_url: (url: String) => void
  open_db: (host: String, port: Number, db: String, user: String, pwd: String) => void
}

declare global {
  interface Window {
    electronAPI: ElectronApi,
  }
}
