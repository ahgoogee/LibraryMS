import { createApp } from 'vue'
import {createRouter,createWebHashHistory} from "vue-router";
import './style.css'
import App from './App.vue'
import {routes} from "./router.js";

const router = createRouter({
    history: createWebHashHistory(),
    routes,
})
router.replace('/login').then()

const app = createApp(App)
app.use(router)
app.mount('#app')
