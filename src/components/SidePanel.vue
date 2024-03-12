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
      id="side-panel-tree"
      :props="treeProps"
      :data="data"
    />
  </div>
</template>

<script lang="js">
import {defineComponent} from 'vue'
import {ElTree, ElTooltip} from 'element-plus'
import logo from '@/assets/logo.svg'

export default defineComponent({
  name: 'SidePanel',
  components: {
    ElTree,
    ElTooltip
  },
  setup() {
    return {
      logo,
    }
  },
  data() {
    return {
      data: [
        {
          label: '尚未连接',
          disabled: true,
          children: []
        }
      ],
      treeProps: {
        label: 'label',
        children: 'children',
        disabled: 'disabled'
      }
    }
  }
})
</script>

<style>
#side-panel-avatar {
  align-content: center;
  padding-top: 25px;
  padding-bottom: 25px;
}

#side-panel-box {
  display: flow;
  width: 160px;
  height: 100vh;
}

#side-panel-avatar-box {
  width: 160px;
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
  width: 160px;
  height: calc(100vh - 120px);
  background: gray;
  color: snow;
}

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