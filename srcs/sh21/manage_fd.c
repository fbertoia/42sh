#include "sh21.h"

int 	change_fd(t_ast_node *root)
{
	int ret;

	ret = 1;
	if (root->piped_cmd)
	{
		if (root->pipe_fd[0] != 0)
		{
			if ((root->tmp_fd_read = dup(0)) < 0)
				ret = 0;
			if (ret && dup2(root->pipe_fd[0], 0) < 0)
				ret = 0;
		}
		if (root->pipe_fd[1] != 1)
		{
			if ((root->tmp_fd_write = dup(1)) < 0)
				ret = 0;
			if (ret && dup2(root->pipe_fd[1], 1) < 0)
				ret = 0;
		}
		if (!ret)
			return (ft_error(errno, "pipe"));
	}
	if (ret && root->redir_node)
		ret = g_exec_fn[root->redir_node->type](root->redir_node);
	return (ret);
}

int 	reset_fd(t_ast_node *root)
{
	// t_fd_cleanup	*fd_cleanup;
	// t_sh21			*sh21;

	// fd_cleanup = sh21->tree.fd_cleanup;
	// while (fd_cleanup)
	// {
	// 	fd_cleanup->fd_function(fd_cleanup);
	// 	fd_cleanup = fd_cleanup->next;
	// }
	// del_list((void **)&sh21->tree.fd_cleanup, &del_redir);
	if (root->piped_cmd)
	{
		if (root->pipe_fd[0] != 0)
			close(root->pipe_fd[0]);
		if (root->pipe_fd[1] != 1)
			close(root->pipe_fd[1]);
	}
}
