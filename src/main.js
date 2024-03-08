import { createApp } from 'vue'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import App from './App.vue'

const my_app = createApp(App)
my_app.use(ElementPlus)
my_app.mount('#app')
