<template>
  <div id="side-panel-box">
    <div id="side-panel-avatar-box">
      <div id="side-panel-avatar">
        <el-tooltip effect="dark" content="关于">
          <img :src=logo alt="" id="side-panel-avatar-el"/>
        </el-tooltip>
      </div>
    </div>
    <el-tree
      ref="tree"
      id="side-panel-tree"
      node-key="id"
      :props="tree_props"
      :data="data"
      default-expanded-keys="[0, 100]"
      v-on:dblclick="on_selected(tree.getCurrentNode())"
    >
    </el-tree>
  </div>
</template>

<script setup lang="ts">
import {ref} from 'vue'
import {ElTree, ElTooltip} from 'element-plus'
import logo from '/logo.svg'

const tree = ref<any>(null);

const tree_props = {
  label: 'label',
  children: 'children',
}

const data = ref([
  {
    id: 0,
    label: '尚未连接',
    children: []
  }
])

defineProps({
  on_selected: {
    type: Function,
    default: (item: any) => {}
  }
})

defineExpose({
  data
})
</script>

<style scoped>
#side-panel-avatar {
  align-content: center;
  padding-top: 25px;
  padding-bottom: 25px;
}

#side-panel-box {
  display: flow;
  width: 180px;
  height: 100vh;
}

#side-panel-avatar-box {
  width: 180px;
  height: 120px;
  background: gray;
}

#side-panel-avatar-el {
  width: 64px;
  height: 64px;
  -webkit-user-select: none;
  -webkit-user-drag: none;
  -webkit-app-region: no-drag;
  cursor: default;
  border-radius: 25%;
}

#side-panel-tree {
  width: 180px;
  height: calc(100vh - 120px);
  background: gray;
  color: snow;
}
</style>

<style>
/* 悬停颜色 */
.el-tree-node__content:hover {
  background-color: lightgray;
}

/* 点击颜色 */
.el-tree-node:focus > .el-tree-node__content {
  background: lightgray;
}

/* 选中颜色 */
.el-tree-node.is-current > .el-tree-node__content {
  background: lightgray;
}
</style>