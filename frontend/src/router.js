import LoginPage from "./pages/LoginPage.vue";
import {createRouter,createWebHashHistory} from "vue-router";
import HelloWorld from "./components/HelloWorld.vue";

export const routes = [
    {
        path:'/',
        component: {template:'<div>This is a home.</div>'}
    },
    {
        path: '/login',
        component: LoginPage
    },
    {
        path: '/hello',
        component: HelloWorld
    }





]
export const router = createRouter({
    history: createWebHashHistory(),
    routes,
})
