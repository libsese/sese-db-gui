<script setup lang="ts">
import {ElTabPane, ElTabs, TabPaneName} from 'element-plus';
import {ref} from "vue";
import WelcomePage from "./WelcomePage.vue";
import TablePage from "./TablePage.vue";

declare type ComponentType = 'WelcomePage' | 'TablePage'

interface TableComponent {
  title: string,
  name: string,
  component_name: ComponentType,
  columns: string[],
  data: object[]
}

let tab_index = 1
const tabs_value = ref('1')
const tabs = ref<TableComponent[]>([
  {
    title: '欢迎',
    name: '1',
    component_name: 'WelcomePage',
    columns: [],
    data: [{}]
  },
])

const switch_component = (component: string) => {
  switch (component) {
    case 'WelcomePage':
      return WelcomePage;
    case 'TablePage':
      return TablePage;
    default:
      return undefined;
  }
}

const add_tab = (component: TableComponent) => {
  const new_tab_name = `${++tab_index}`
  component.name = new_tab_name
  tabs.value.push(component)
  tabs_value.value = new_tab_name
}

const remove_tab = (target_name: TabPaneName) => {
  const raw_tabs = tabs.value
  let active_name = tabs_value.value
  if (active_name === target_name) {
    raw_tabs.forEach((tab, index) => {
      if (tab.name === target_name) {
        const next_tab = raw_tabs[index + 1] || raw_tabs[index - 1]
        if (next_tab) {
          active_name = next_tab.name
        }
      }
    })
  }

  tabs_value.value = active_name
  tabs.value = raw_tabs.filter((tab) => tab.name !== target_name)
}

defineExpose({
  add_tab
})

</script>

<template>
  <div class="page-panel-box">
    <el-tabs v-model="tabs_value" type="border-card" class="page-box" closable @tab-remove="remove_tab">
      <slot/>
      <el-tab-pane
        v-for="item in tabs"
        :key="item.name"
        :label="item.title"
        :name="item.name">
        <component :is="switch_component(item.component_name)" :columns="item.columns" :data="item.data"/>
      </el-tab-pane>
    </el-tabs>
  </div>
</template>

<style scoped>
.page-panel-box {
  width: 100%;
  height: 100%;
}

.page-box {
  width: 100%;
  height: 100%;
}
</style>